# robot_shared/cmake/modules/DetectUnitreeSDK.cmake
include_guard(GLOBAL)
include(${CMAKE_CURRENT_LIST_DIR}/../core/ColorMessage.cmake)

option(USE_UNITREE_SDK "Enable Unitree SDK support" ${IS_LINUX})
if(USE_UNITREE_SDK)
    add_compile_definitions(USE_UNITREE_SDK)
endif()
color_message(STATUS cyan "[INFO] USE_UNITREE_SDK: ${USE_UNITREE_SDK}")
