#pragma once
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "utility/logger.h"  

namespace cli { 
  inline void to_lower(std::string& s){
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
  }

  // 通用合法性检查模板
  inline bool validate_option(
      const std::string& name,
      const std::string& value,
      const std::vector<std::string>& valid_list)
  {
    if (std::find(valid_list.begin(), valid_list.end(), value) == valid_list.end()) {
      std::ostringstream oss;
      oss << "Available: ";
      for (size_t i = 0; i < valid_list.size(); ++i) {
        oss << valid_list[i];
        if (i != valid_list.size() - 1) oss << " | ";
      }
      FRC_ERROR("Invalid "<< name << ": " << value);
      FRC_ERROR(oss.str());
      return false;
    }
    return true;
  }
} // namespace cli
