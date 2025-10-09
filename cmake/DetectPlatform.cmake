# ======================================================================
# DetectPlatform.cmake
# Detect current OS, architecture, and platform profile
# ======================================================================

include_guard(GLOBAL)

if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(CURRENT_PLATFORM "macos")
    set(IS_LINUX OFF)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(IS_LINUX ON)
    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
        set(CURRENT_PLATFORM "linux-x86_64")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64|ARM64")
        set(CURRENT_PLATFORM "linux-aarch64")
    else()
        color_message(FATAL_ERROR red "[ERROR] Unsupported Linux architecture: ${CMAKE_SYSTEM_PROCESSOR}")
    endif()
else()
    color_message(FATAL_ERROR red "[ERROR] Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

# ---- Diagnostic Output ----
color_message(STATUS cyan "[INFO] ========== Platform Detection ==========")
color_message(STATUS cyan "[INFO] OS: ${CMAKE_SYSTEM_NAME}")
color_message(STATUS cyan "[INFO] Arch: ${CMAKE_SYSTEM_PROCESSOR}")
color_message(STATUS cyan "[INFO] ========================================")

