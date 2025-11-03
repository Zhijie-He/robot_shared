#pragma once

#include <string>
#include <filesystem>
#include <unistd.h>

inline std::string getPath(const std::string& subpath = "")
{
    char exePath[1024];
    ssize_t len = readlink("/proc/self/exe", exePath, sizeof(exePath) - 1);
    if (len != -1) {
        exePath[len] = '\0';
        std::filesystem::path exeDir = std::filesystem::path(exePath).parent_path();
        auto installRoot = (exeDir / "../share/policy_deploy").lexically_normal();
        if (std::filesystem::exists(installRoot))
            return (installRoot / subpath).lexically_normal().string();
    }
#ifdef PROJECT_SOURCE_DIR
    return (std::filesystem::path(PROJECT_SOURCE_DIR) / subpath).lexically_normal().string();
#else
    return (std::filesystem::current_path() / subpath).lexically_normal().string();
#endif
}

