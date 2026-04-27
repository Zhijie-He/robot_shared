#pragma once

#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <mutex>
#include "translation.hpp"

// if enable color printing 
#ifndef LOG_USE_COLOR
#define LOG_USE_COLOR 1
#endif

// if enable print prefix [INFO time file:line]
#ifndef LOG_USE_PREFIX
#define LOG_USE_PREFIX 1
#endif

// if enable debug print (otherwise not utilize DBG_INFO）
#ifndef LOG_ENABLE_DEBUG
#define LOG_ENABLE_DEBUG 0
#endif

// ------------------------ color define ------------------------
#if LOG_USE_COLOR
  #define COLOR_RESET      "\033[0m"
  #define COLOR_INFO       "\033[1;32m"
  #define COLOR_WARN       "\033[1;33m"
  #define COLOR_ERROR      "\033[1;31m"
  #define COLOR_DEBUG      "\033[1;34m"
  #define COLOR_SUCCESS    "\033[1;92m"       // light green
  #define COLOR_HIGHLIGHT  "\033[1;35m"       // magenta
  #define COLOR_CRITICAL   "\033[1;97;41m"    // white lettering on a red background
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


// time str
inline std::string current_time_str() {
  std::time_t now = std::time(nullptr);
  std::stringstream ss;
  ss << std::put_time(std::localtime(&now), "%H:%M:%S");
  return ss.str();
}

// remove [xxx] tag
inline std::string strip_bracket_prefix(const std::string& msg) {
#if !LOG_USE_PREFIX
  if (!msg.empty() && msg[0] == '[') {
    size_t end = msg.find(']');
    if (end != std::string::npos && end + 1 < msg.size()) {
      size_t start = end + 1;
      if(msg[start] == ' ') ++start;
      return msg.substr(start);  // remove [xxx]
    }
  }
#endif
  return msg;
}

// print log to file
inline void log_to_file(const std::string& msg) {
  if (!GlobalSettings::isLogEnabled()) return;
  static std::ofstream file;
  static std::mutex mtx;
  static bool initialized = false;
  
  std::lock_guard<std::mutex> lock(mtx);
  if(!initialized){
    initialized = true;
    const auto& path = GlobalSettings::getLogPath();

    if(!path.empty()) file.open(path, std::ios::app);
  }
  if(file.is_open()){
    file << msg;
    file.flush();
  }
}

// log prefix
#if LOG_USE_PREFIX
  #define FRC_PREFIX(level, color) color "[" level " " << current_time_str() << " " << __FILE__ << ":" << __LINE__ << "] "
#else
  #define FRC_PREFIX(level, color) color "[" level "] "
#endif

// auto translation
#define FRC_TRANSLATE(msg) Translation::autoTranslate(msg)

// log marco define
#define FRC_INFO(x) \
do { \
  std::ostringstream _os; _os << x; \
  std::ostringstream _tmp; \
  _tmp << FRC_PREFIX("INFO", COLOR_INFO)     << FRC_TRANSLATE(_os.str()) << COLOR_RESET << "\n"; \
  std::cout << _tmp.str(); \
  log_to_file(_tmp.str()); \
} while(0)

#define FRC_WARN(x) \
do { std::ostringstream _os; _os << x; \
  std::ostringstream _tmp; \
  _tmp << FRC_PREFIX("WARN", COLOR_WARN)     << FRC_TRANSLATE(_os.str()) << COLOR_RESET << "\n"; \
  std::cout << _tmp.str(); \
  log_to_file(_tmp.str()); \
} while(0)

#define FRC_ERROR(x) \
do { \
  std::ostringstream _os; _os << x; \
  std::ostringstream _tmp; \
  _tmp << FRC_PREFIX("ERROR", COLOR_ERROR)   << FRC_TRANSLATE(_os.str()) << COLOR_RESET << "\n"; \
  std::cerr << _tmp.str(); \
  log_to_file(_tmp.str()); \
} while(0)

#define FRC_SUCCESS(x) \
do { \
  std::ostringstream _os; _os << x; \
  std::ostringstream _tmp; \
  _tmp << FRC_PREFIX("SUCCESS", COLOR_SUCCESS) << FRC_TRANSLATE(_os.str()) << COLOR_RESET << "\n"; \
  std::cout << _tmp.str(); \
  log_to_file(_tmp.str()); \
} while(0)

#define FRC_HIGHLIGHT(x) \
do { \
  std::ostringstream _os; _os << x; \
  std::ostringstream _tmp; \
  _tmp << FRC_PREFIX("HIGHLIGHT", COLOR_HIGHLIGHT) << FRC_TRANSLATE(_os.str()) << COLOR_RESET << "\n"; \
  std::cout << _tmp.str(); \
  log_to_file(_tmp.str()); \
} while(0)

#define FRC_CRITICAL(x)  \
do { \
  std::ostringstream _os; _os << x; \
  std::ostringstream _tmp; \
  _tmp << FRC_PREFIX("CRITICAL", COLOR_CRITICAL) << FRC_TRANSLATE(_os.str()) << COLOR_RESET << "\n"; \
  std::cerr << _tmp.str(); \
  log_to_file(_tmp.str()); \
} while(0)

#if LOG_ENABLE_DEBUG
  #define DBG_INFO(x)\
  do { \
    std::ostringstream _os; _os << x; \
    std::ostringstream _tmp; \
    _tmp << FRC_PREFIX("DEBUG", COLOR_DEBUG)   << FRC_TRANSLATE(_os.str()) << COLOR_RESET << "\n"; \
    std::cout << _tmp.str(); \
    log_to_file(_tmp.str()); \
  } while(0)
#else
  #define DBG_INFO(x)
#endif
