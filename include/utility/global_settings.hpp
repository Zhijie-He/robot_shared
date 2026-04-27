#pragma once
#include <string>

enum class Lang { EN, ZH };

class GlobalSettings {
public:
    // ===== Language =====
    static void setLanguage(Lang lang) { language() = lang; }
    static Lang getLanguage() { return language(); }

    static Lang parseLanguage(const std::string& s) {
        if (s == "zh" || s == "ZH" || s == "cn" || s == "CN")
            return Lang::ZH;
        return Lang::EN;
    }

    // ===== Log Enable =====
    static void setLogEnabled(bool enabled) { logEnabled() = enabled; }
    static bool isLogEnabled() { return logEnabled(); }

    // ===== Log File Path =====
    static void setLogPath(const std::string& path) { 
        std::string filename = "log.txt";
        logPath() = path + "/" + filename; 
    }
    static const std::string& getLogPath() { return logPath(); }

private:
    // language
    static Lang& language() {
        static Lang lang = Lang::EN;
        return lang;
    }

    // log enable
    static bool& logEnabled() {
        static bool enabled = true;  
        return enabled;
    }

    // log path
    static std::string& logPath() {
        static std::string path = ""; 
        return path;
    }
};
