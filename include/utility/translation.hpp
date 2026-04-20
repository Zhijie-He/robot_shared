#pragma once
#include <regex>
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

        const auto& sub_table = (lang == Lang::EN) ? TranslationData::SUB_EN
                                               : TranslationData::SUB_ZH;
        static std::string replaced_it;
        replaced_it = key;  // 用于最终返回
        for (const auto& [k, v] : sub_table) {
            size_t pos = replaced_it.find(k);
            if (pos != std::string::npos) {
                replaced_it.replace(pos, k.size(), v);
                return replaced_it;
            }
        }

        // 未找到翻译就原样返回 key
        static std::string missing;
        missing = key;
        return missing;
    }
    //  get(key): 仅翻译 key，不含前缀逻辑
    static const std::string& get_code(const std::string& key)
    {
        const auto& table = TranslationData::MARKER_CODE;
        auto it = table.find(key);
        if (it != table.end())
            return it->second;

        const auto& sub_table = TranslationData::SUB_MARKER_CODE;
        static std::string code_it;
        code_it = key;  // 用于最终返回
        for (const auto& [k, v] : sub_table) {
            size_t pos = code_it.find(k);
            if (pos != std::string::npos) {
                return v;
            }
        }

        static const std::string empty;
        return empty;
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

#ifdef USE_WEBCTRL
        const std::string& code_prefix = get_code(key);
        if (!code_prefix.empty())
            return code_prefix + " " + translated;
        else
            return translated;
#endif

        // 若关闭前缀显示，则直接返回翻译后的内容
#if LOG_USE_PREFIX
        if (!prefix.empty())
            return prefix + " " + translated;
#endif

        return translated;
    }
};

#define LANG(key) Translation::get(key)