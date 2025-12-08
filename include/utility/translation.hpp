#pragma once
#include <string>
#include "global_settings.hpp"
#include "translation_data.hpp"

// Translation: 自动翻译模块（支持自动解析前缀 [Main] xxx）
class Translation {
public:
    //  get(key): 仅翻译 key，不含前缀逻辑
    static const std::string& get(const std::string& key)
    {
        Lang lang = GlobalSettings::getLanguage();
        const auto& table = (lang == Lang::EN) ? TranslationData::EN
                                               : TranslationData::ZH;

        auto it = table.find(key);
        if (it != table.end())
            return it->second;

        // 未找到翻译就原样返回 key
        static std::string missing;
        missing = key;
        return missing;
    }

    // autoTranslate(msg): 支持解析 [Prefix] key 并恢复前缀
    static std::string autoTranslate(const std::string& msg)
    {
        if (msg.empty())
            return msg;

        std::string prefix;       // 如 "[Main]"
        std::string key = msg;    // 要翻译的字符串

        // 若存在 [xxx] 前缀，则提取它
        if (msg[0] == '[') {
            size_t end = msg.find(']');
            if (end != std::string::npos) {
                prefix = msg.substr(0, end + 1); // "[Main]"

                size_t start = end + 1;
                if (start < msg.size() && msg[start] == ' ')
                    start++;

                key = msg.substr(start);  // 提取真正需要翻译的部分
            }
        }

        // 翻译 key
        const std::string& translated = get(key);

        // 若关闭前缀显示，则直接返回翻译后的内容
#if LOG_USE_PREFIX
        if (!prefix.empty())
            return prefix + " " + translated;
#endif

        return translated;
    }
};

#define LANG(key) Translation::get(key)

