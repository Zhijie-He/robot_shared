#pragma once

#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

// 🧠 是否启用彩色输出
#ifndef LOG_USE_COLOR
#define LOG_USE_COLOR 1
#endif

// 🧠 是否启用前缀 [INFO time file:line]
#ifndef LOG_USE_PREFIX
#define LOG_USE_PREFIX 1
#endif

// 🧠 是否启用 DEBUG 输出（不定义则不会打印 DBG_INFO）
#ifndef LOG_ENABLE_DEBUG
#define LOG_ENABLE_DEBUG 0
#endif

// 🎨 彩色控制字符（根据开关选择）
// ------------------------ 颜色定义 ------------------------
#if LOG_USE_COLOR
  #define COLOR_RESET      "\033[0m"
  #define COLOR_INFO       "\033[1;32m"
  #define COLOR_WARN       "\033[1;33m"
  #define COLOR_ERROR      "\033[1;31m"
  #define COLOR_DEBUG      "\033[1;34m"
  #define COLOR_SUCCESS    "\033[1;92m"       // 亮绿色
  #define COLOR_HIGHLIGHT  "\033[1;35m"       // 品红（高亮信息）
  #define COLOR_CRITICAL   "\033[1;97;41m"    // 白字红底
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


// 🕒 当前时间字符串
inline std::string current_time_str() {
    std::time_t now = std::time(nullptr);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now), "%H:%M:%S");
    return ss.str();
}

// 🧩 去除日志开头的 [xxx] 模块标签
inline std::string strip_bracket_prefix(const std::string& msg) {
#if !LOG_USE_PREFIX
  if (!msg.empty() && msg[0] == '[') {
    size_t end = msg.find(']');
    if (end != std::string::npos && end + 1 < msg.size()) {
      size_t start = end + 1;
      if(msg[start] == ' ') ++start;
      return msg.substr(start);  // 去掉 [xxx]
    }
  }
#endif
  return msg;
}

// 📦 日志前缀
#if LOG_USE_PREFIX
  #define FRC_PREFIX(level, color) color "[" level " " << current_time_str() << " " << __FILE__ << ":" << __LINE__ << "] "
#else
  #define FRC_PREFIX(level, color) color "[" level "] "
#endif

// ✅ 日志宏定义
// ------------------------ 日志宏定义 ------------------------
// #define FRC_INFO(x)      std::cout << FRC_PREFIX("INFO",    COLOR_INFO)     << strip_bracket_prefix(x) << COLOR_RESET << std::endl
// #define FRC_WARN(x)      std::cout << FRC_PREFIX("WARN",    COLOR_WARN)     << strip_bracket_prefix(x) << COLOR_RESET << std::endl
// #define FRC_ERROR(x)     std::cerr << FRC_PREFIX("ERROR",   COLOR_ERROR)    << strip_bracket_prefix(x) << COLOR_RESET << std::endl
// #define FRC_SUCCESS(x)   std::cout << FRC_PREFIX("SUCCESS", COLOR_SUCCESS)  << strip_bracket_prefix(x) << COLOR_RESET << std::endl
// #define FRC_HIGHLIGHT(x) std::cout << FRC_PREFIX("HIGHLIGHT", COLOR_HIGHLIGHT) << strip_bracket_prefix(x) << COLOR_RESET << std::endl
// #define FRC_CRITICAL(x)  std::cerr << FRC_PREFIX("CRITICAL", COLOR_CRITICAL) << strip_bracket_prefix(x) << COLOR_RESET << std::endl

// #if LOG_ENABLE_DEBUG
//   #define DBG_INFO(x)  std::cout << FRC_PREFIX("DEBUG", COLOR_DEBUG) << strip_bracket_prefix(x) << COLOR_RESET << std::endl
// #else
//   #define DBG_INFO(x)
// #endif

// ✅ 日志宏定义（增强版，支持 << 表达式 + 自动去掉 [xxx]）
#define FRC_INFO(x)      do { std::ostringstream _os; _os << x; std::cout << FRC_PREFIX("INFO", COLOR_INFO)     << strip_bracket_prefix(_os.str()) << COLOR_RESET << std::endl; } while(0)
#define FRC_WARN(x)      do { std::ostringstream _os; _os << x; std::cout << FRC_PREFIX("WARN", COLOR_WARN)     << strip_bracket_prefix(_os.str()) << COLOR_RESET << std::endl; } while(0)
#define FRC_ERROR(x)     do { std::ostringstream _os; _os << x; std::cerr << FRC_PREFIX("ERROR", COLOR_ERROR)   << strip_bracket_prefix(_os.str()) << COLOR_RESET << std::endl; } while(0)
#define FRC_SUCCESS(x)   do { std::ostringstream _os; _os << x; std::cout << FRC_PREFIX("SUCCESS", COLOR_SUCCESS) << strip_bracket_prefix(_os.str()) << COLOR_RESET << std::endl; } while(0)
#define FRC_HIGHLIGHT(x) do { std::ostringstream _os; _os << x; std::cout << FRC_PREFIX("HIGHLIGHT", COLOR_HIGHLIGHT) << strip_bracket_prefix(_os.str()) << COLOR_RESET << std::endl; } while(0)
#define FRC_CRITICAL(x)  do { std::ostringstream _os; _os << x; std::cerr << FRC_PREFIX("CRITICAL", COLOR_CRITICAL) << strip_bracket_prefix(_os.str()) << COLOR_RESET << std::endl; } while(0)

#if LOG_ENABLE_DEBUG
  #define DBG_INFO(x)    do { std::ostringstream _os; _os << x; std::cout << FRC_PREFIX("DEBUG", COLOR_DEBUG)   << strip_bracket_prefix(_os.str()) << COLOR_RESET << std::endl; } while(0)
#else
  #define DBG_INFO(x)
#endif
