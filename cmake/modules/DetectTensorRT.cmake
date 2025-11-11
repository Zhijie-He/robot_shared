# robot_shared/cmake/DetectTensorRT.cmake
include_guard(GLOBAL)
include(${CMAKE_CURRENT_LIST_DIR}/../core/ColorMessage.cmake)

set(TENSORRT_DIR $ENV{TENSORRT_DIR}) 
# 默认开启 TensorRT，除非用户显式关闭
if(NOT DEFINED USE_TENSORRT)
    set(USE_TENSORRT ON)
endif()

# 如果被用户禁用，则直接退出
if(NOT USE_TENSORRT)
    color_message(STATUS cyan "[INFO] TensorRT manually disabled.")
    return()
endif()

set(NVINFER_MAJOR 0)
if(DEFINED TENSORRT_DIR)
    set(USE_TENSORRT ON)
    color_message(STATUS cyan "[INFO] USE_TENSORRT: ${USE_TENSORRT} (${TENSORRT_DIR})")
    
    # 平台区分
    if(CURRENT_PLATFORM STREQUAL "linux-x86_64")
        set(_TRT_HEADER "${TENSORRT_DIR}/include/NvInferVersion.h")
    elseif(CURRENT_PLATFORM STREQUAL "linux-aarch64")
        set(_TRT_HEADER "/usr/include/aarch64-linux-gnu/NvInferVersion.h")
    endif()

    if(NOT EXISTS "${_TRT_HEADER}")
        message(FATAL_ERROR "TensorRT header not found: ${_TRT_HEADER}")
    endif()

    # 提取版本号
    file(READ "${_TRT_HEADER}" NVCONTENT)
    string(REGEX MATCH "#define[ \t]+TRT_MAJOR_ENTERPRISE[ \t]+([0-9]+)" _m "${NVCONTENT}")
    if(CMAKE_MATCH_1)
        set(NVINFER_MAJOR "${CMAKE_MATCH_1}")
    else()
        string(REGEX MATCH "#define[ \t]+NV_TENSORRT_MAJOR[ \t]+([0-9]+)" _m2 "${NVCONTENT}")
        set(NVINFER_MAJOR "${CMAKE_MATCH_1}")
    endif()
    color_message(STATUS cyan "[INFO] Detected TensorRT major version: ${NVINFER_MAJOR}")
else()
    set(USE_TENSORRT OFF)
    color_message(STATUS cyan "[INFO] USE_TENSORRT: ${USE_TENSORRT} (TENSORRT_DIR not set or invalid ${TENSORRT_DIR})")
endif()
