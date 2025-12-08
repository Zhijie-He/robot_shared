#pragma once
#include <string>

enum class Lang { EN, ZH };

class GlobalSettings {
public:
    static void setLanguage(Lang lang) { language() = lang; }
    static Lang getLanguage() { return language(); }

    static Lang parseLanguage(const std::string& s) {
        if (s == "zh" || s == "ZH" || s == "cn" || s == "CN")
            return Lang::ZH;
        return Lang::EN;
    }

private:
    static Lang& language() {
        static Lang lang = Lang::EN;
        return lang;
    }
};

