#pragma once

#include <chrono>
#include <iomanip>
#include <cstddef>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include <condition_variable>

#include "translation.hpp"

// ============================================================
// Configuration
// ============================================================

#ifndef LOG_USE_COLOR
#define LOG_USE_COLOR 1
#endif

#ifndef LOG_USE_PREFIX
#define LOG_USE_PREFIX 1
#endif

#ifndef LOG_ENABLE_DEBUG
#define LOG_ENABLE_DEBUG 0
#endif

// Async queue size, similar to spdlog default value
#ifndef LOG_ASYNC_QUEUE_SIZE
#define LOG_ASYNC_QUEUE_SIZE 8192
#endif

// Periodically flush file every 1 second
#ifndef LOG_ASYNC_FLUSH_INTERVAL_MS
#define LOG_ASYNC_FLUSH_INTERVAL_MS 10000
#endif


// ============================================================
// Color define
// ============================================================

#if LOG_USE_COLOR

#define COLOR_RESET      "\033[0m"
#define COLOR_INFO       "\033[1;32m"
#define COLOR_WARN       "\033[1;33m"
#define COLOR_ERROR      "\033[1;31m"
#define COLOR_DEBUG      "\033[1;34m"
#define COLOR_SUCCESS    "\033[1;92m"
#define COLOR_HIGHLIGHT  "\033[1;35m"
#define COLOR_CRITICAL   "\033[1;97;41m"

#else

#define COLOR_RESET      ""
#define COLOR_INFO       ""
#define COLOR_WARN       ""
#define COLOR_ERROR      ""
#define COLOR_DEBUG      ""
#define COLOR_SUCCESS    ""
#define COLOR_HIGHLIGHT  ""
#define COLOR_CRITICAL   ""

#endif


// ============================================================
// Async logger policy
// ============================================================

enum class AsyncLogStream {
  NONE,
  STDOUT,
  STDERR
};

enum class AsyncOverflowPolicy {
  BLOCK,
  OVERRUN_OLDEST,
  DISCARD_NEW
};


// For robot control, do not block the control thread by default.
#ifndef LOG_ASYNC_OVERFLOW_POLICY
#define LOG_ASYNC_OVERFLOW_POLICY \
  AsyncOverflowPolicy::OVERRUN_OLDEST
#endif


// ============================================================
// Utility functions
// ============================================================

inline std::string current_time_str() {
  const std::time_t now = std::time(nullptr);

  std::tm local_time{};

#if defined(_WIN32)
  localtime_s(&local_time, &now);
#else
  localtime_r(&now, &local_time);
#endif

  std::ostringstream ss;
  ss << std::put_time(&local_time, "%H:%M:%S");

  return ss.str();
}


// Remove [xxx] prefix when LOG_USE_PREFIX is disabled.
inline std::string strip_bracket_prefix(const std::string& msg) {
#if !LOG_USE_PREFIX
  if (!msg.empty() && msg[0] == '[') {
    const std::size_t end = msg.find(']');

    if (end != std::string::npos && end + 1 < msg.size()) {
      std::size_t start = end + 1;

      if (msg[start] == ' ') {
        ++start;
      }

      return msg.substr(start);
    }
  }
#endif

  return msg;
}


// Remove ANSI color escape sequences before writing to file.
inline std::string strip_ansi_codes(const std::string& input) {
  std::string output;
  output.reserve(input.size());

  bool escape = false;
  bool csi = false;

  for (unsigned char ch : input) {
    if (!escape) {
      if (ch == 0x1B) {
        escape = true;
        csi = false;
      } else {
        output.push_back(static_cast<char>(ch));
      }
    } else if (!csi) {
      if (ch == '[') {
        csi = true;
      } else {
        escape = false;
      }
    } else {
      // ANSI CSI sequence ends with a character between @ and ~.
      if (ch >= 0x40 && ch <= 0x7E) {
        escape = false;
        csi = false;
      }
    }
  }

  return output;
}


// ============================================================
// Async logger
// ============================================================

class AsyncLogger {
private:
  struct LogItem {
    std::string message;
    AsyncLogStream stream;
    bool write_file;
    bool force_flush_file;

    LogItem()
        : stream(AsyncLogStream::NONE),
          write_file(false),
          force_flush_file(false) {}
  };

public:
  static AsyncLogger& instance() {
    static AsyncLogger logger;
    return logger;
  }

  AsyncLogger(const AsyncLogger&) = delete;
  AsyncLogger& operator=(const AsyncLogger&) = delete;

  void submit(std::string message, AsyncLogStream stream, bool force_flush_file = false) {
    // This check is performed in the caller thread.
    // Console output is still preserved when file logging is disabled.
    const bool write_file = GlobalSettings::isLogEnabled();
    std::unique_lock<std::mutex> lock(mutex_);

    if (stopping_) {
      return;
    }

    if (size_ == capacity_) {
      switch (overflow_policy_) {
        case AsyncOverflowPolicy::BLOCK: {
          not_full_.wait(lock, [this]() {
            return size_ < capacity_ || stopping_;
          });

          if (stopping_) {
            return;
          }

          break;
        }

        case AsyncOverflowPolicy::OVERRUN_OLDEST: {
          // Remove the oldest message and reuse its slot.
          head_ = (head_ + 1) % capacity_;
          --size_;
          break;
        }

        case AsyncOverflowPolicy::DISCARD_NEW: {
          return;
        }
      }
    }

    LogItem& slot = queue_[tail_];

    slot.message = std::move(message);
    slot.stream = stream;
    slot.write_file = write_file;
    slot.force_flush_file = force_flush_file;

    tail_ = (tail_ + 1) % capacity_;
    ++size_;

    lock.unlock();
    not_empty_.notify_one();
  }

  void shutdown() {
    {
      std::lock_guard<std::mutex> lock(mutex_);
      stopping_ = true;
    }

    not_empty_.notify_all();
    not_full_.notify_all();

    if (worker_.joinable() && worker_.get_id() != std::this_thread::get_id()) {
      worker_.join();
    }
  }

private:
  AsyncLogger()
      : capacity_(LOG_ASYNC_QUEUE_SIZE > 0 ? LOG_ASYNC_QUEUE_SIZE : 1),
        queue_(capacity_),
        overflow_policy_(LOG_ASYNC_OVERFLOW_POLICY),
        head_(0),
        tail_(0),
        size_(0),
        stopping_(false) {
    worker_ = std::thread(&AsyncLogger::workerLoop, this);
  }

  ~AsyncLogger() {
    shutdown();
  }

  void workerLoop() {
    std::ofstream file;
    bool file_initialized = false;

    const auto flush_interval = std::chrono::milliseconds(LOG_ASYNC_FLUSH_INTERVAL_MS);
    auto next_flush = std::chrono::steady_clock::now() + flush_interval;

    while (true) {
      LogItem item;
      bool has_item = false;

      {
        std::unique_lock<std::mutex> lock(mutex_);

        if (size_ == 0 && !stopping_) {
          if (flush_interval.count() > 0) {
            not_empty_.wait_until(
                lock,
                next_flush,
                [this]() {
                  return stopping_ || size_ > 0;
                });
          } else {
            not_empty_.wait(
                lock,
                [this]() {
                  return stopping_ || size_ > 0;
                });
          }
        }

        if (size_ > 0) {
          LogItem& slot = queue_[head_];

          item.message = std::move(slot.message);
          item.stream = slot.stream;
          item.write_file = slot.write_file;
          item.force_flush_file = slot.force_flush_file;

          head_ = (head_ + 1) % capacity_;
          --size_;

          has_item = true;

          lock.unlock();
          not_full_.notify_one();
        } else if (stopping_) {
          break;
        }
      }

      if (has_item) {
        processItem(item, file, file_initialized);
      }

      // Periodic flush, similar to spdlog::flush_every().
      if (flush_interval.count() > 0) {
        const auto now = std::chrono::steady_clock::now();

        if (now >= next_flush) {
          if (file.is_open()) {
            file.flush();
          }

          next_flush = now + flush_interval;
        }
      }
    }

    // Flush all remaining buffered data before worker exits.
    if (file.is_open()) {
      file.flush();
    }
  }

  void processItem(const LogItem& item, std::ofstream& file, bool& file_initialized) {
    const auto message_size = static_cast<std::streamsize>(item.message.size());

    // --------------------------------------------------------
    // Console sink
    // --------------------------------------------------------

    if (item.stream == AsyncLogStream::STDOUT) {
      std::cout.write(item.message.data(), message_size);
      std::cout.flush();
    } else if (item.stream == AsyncLogStream::STDERR) {
      std::cerr.write(item.message.data(), message_size);
      std::cerr.flush();
    }

    // --------------------------------------------------------
    // File sink
    // --------------------------------------------------------

    if (!item.write_file) {
      return;
    }

    // Lazy initialization. This supports enabling file logging
    // after the logger has already been created.
    if (!file_initialized) {
      file_initialized = true;

      const auto& path = GlobalSettings::getLogPath();

      if (!path.empty()) {
        file.open(path, std::ios::out | std::ios::app);
      }
    }

    if (!file.is_open()) {
      return;
    }

#if LOG_USE_COLOR
    // Console keeps color; file removes ANSI color codes.
    const std::string plain_message = strip_ansi_codes(item.message);

    file.write(
        plain_message.data(),
        static_cast<std::streamsize>(plain_message.size()));
#else
    file.write(item.message.data(), message_size);
#endif

    if (item.force_flush_file) {
      file.flush();
    }
  }

private:
  const std::size_t capacity_;
  std::vector<LogItem> queue_;

  AsyncOverflowPolicy overflow_policy_;

  std::size_t head_;
  std::size_t tail_;
  std::size_t size_;

  bool stopping_;

  std::mutex mutex_;
  std::condition_variable not_empty_;
  std::condition_variable not_full_;

  std::thread worker_;
};


// ============================================================
// Public logging functions
// ============================================================

inline void async_log(std::string message, AsyncLogStream stream, bool force_flush_file = false) {
  AsyncLogger::instance().submit(
      std::move(message),
      stream,
      force_flush_file);
}


// Keep compatibility with the previous interface.
inline void log_to_file(std::string message, bool force_flush = false) {
  AsyncLogger::instance().submit(
      std::move(message),
      AsyncLogStream::NONE,
      force_flush);
}


// Auto translation
#define FRC_TRANSLATE(msg) Translation::autoTranslate(msg)

// Log prefix
#if LOG_USE_PREFIX

#define FRC_PREFIX(level, color) \
  color "[" level " " << current_time_str() << " " \
  << __FILE__ << ":" << __LINE__ << "] "

#else

#define FRC_PREFIX(level, color) \
  color "[" level "] "

#endif


// ============================================================
// Log macros
// ============================================================

#define FRC_INFO(x) \
do { \
  std::ostringstream _os; \
  _os << x; \
  std::ostringstream _tmp; \
  _tmp << FRC_PREFIX("INFO", COLOR_INFO) \
       << FRC_TRANSLATE(_os.str()) \
       << COLOR_RESET << "\n"; \
  async_log(_tmp.str(), AsyncLogStream::STDOUT, false); \
} while (0)


#define FRC_WARN(x) \
do { \
  std::ostringstream _os; \
  _os << x; \
  std::ostringstream _tmp; \
  _tmp << FRC_PREFIX("WARN", COLOR_WARN) \
       << FRC_TRANSLATE(_os.str()) \
       << COLOR_RESET << "\n"; \
  async_log(_tmp.str(), AsyncLogStream::STDOUT, false); \
} while (0)


#define FRC_ERROR(x) \
do { \
  std::ostringstream _os; \
  _os << x; \
  std::ostringstream _tmp; \
  _tmp << FRC_PREFIX("ERROR", COLOR_ERROR) \
       << FRC_TRANSLATE(_os.str()) \
       << COLOR_RESET << "\n"; \
  async_log(_tmp.str(), AsyncLogStream::STDERR, true); \
} while (0)


#define FRC_SUCCESS(x) \
do { \
  std::ostringstream _os; \
  _os << x; \
  std::ostringstream _tmp; \
  _tmp << FRC_PREFIX("SUCCESS", COLOR_SUCCESS) \
       << FRC_TRANSLATE(_os.str()) \
       << COLOR_RESET << "\n"; \
  async_log(_tmp.str(), AsyncLogStream::STDOUT, false); \
} while (0)


#define FRC_HIGHLIGHT(x) \
do { \
  std::ostringstream _os; \
  _os << x; \
  std::ostringstream _tmp; \
  _tmp << FRC_PREFIX("HIGHLIGHT", COLOR_HIGHLIGHT) \
       << FRC_TRANSLATE(_os.str()) \
       << COLOR_RESET << "\n"; \
  async_log(_tmp.str(), AsyncLogStream::STDOUT, false); \
} while (0)


#define FRC_CRITICAL(x) \
do { \
  std::ostringstream _os; \
  _os << x; \
  std::ostringstream _tmp; \
  _tmp << FRC_PREFIX("CRITICAL", COLOR_CRITICAL) \
       << FRC_TRANSLATE(_os.str()) \
       << COLOR_RESET << "\n"; \
  async_log(_tmp.str(), AsyncLogStream::STDERR, true); \
} while (0)


#if LOG_ENABLE_DEBUG

#define DBG_INFO(x) \
do { \
  std::ostringstream _os; \
  _os << x; \
  std::ostringstream _tmp; \
  _tmp << FRC_PREFIX("DEBUG", COLOR_DEBUG) \
       << FRC_TRANSLATE(_os.str()) \
       << COLOR_RESET << "\n"; \
  async_log(_tmp.str(), AsyncLogStream::STDOUT, false); \
} while (0)

#else

#define DBG_INFO(x) \
do { \
} while (0)

#endif
