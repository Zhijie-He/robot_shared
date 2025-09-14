# robot_shared/cmake/ColorMessage.cmake
option(ENABLE_COLOR_LOG "Enable colorized message output" ON)

function(color_message TYPE COLOR TEXT)
    if(NOT ENABLE_COLOR_LOG)
        message(${TYPE} "${TEXT}")
        return()
    endif()

    string(ASCII 27 Esc)
    set(RESET "${Esc}[0m")

    if(COLOR STREQUAL "red")
        set(COLOR_CODE "${Esc}[1;31m")
    elseif(COLOR STREQUAL "green")
        set(COLOR_CODE "${Esc}[1;32m")
    elseif(COLOR STREQUAL "yellow")
        set(COLOR_CODE "${Esc}[1;33m")
    elseif(COLOR STREQUAL "blue")
        set(COLOR_CODE "${Esc}[1;34m")
    elseif(COLOR STREQUAL "cyan")
        set(COLOR_CODE "${Esc}[1;36m")
    else()
        set(COLOR_CODE "")
    endif()

    message(${TYPE} "${COLOR_CODE}${TEXT}${RESET}")
endfunction()

