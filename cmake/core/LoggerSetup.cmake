# robot_shared/cmake/core/LoggerSetup.cmake
include_guard(GLOBAL)
include(${CMAKE_CURRENT_LIST_DIR}/ColorMessage.cmake)

add_compile_definitions(LOG_USE_COLOR=1)
if(ENCRYPTION)
    add_compile_definitions(LOG_USE_PREFIX=0 LOG_ENABLE_DEBUG=0)
    color_message(STATUS cyan "[INFO] Logger: encryption mode (no debug)")
else()
    add_compile_definitions(LOG_USE_PREFIX=1 LOG_ENABLE_DEBUG=1)
    color_message(STATUS cyan "[INFO] Logger: standard debug mode")
endif()

