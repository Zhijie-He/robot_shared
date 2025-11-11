# robot_shared/cmake/AddressSanitizer.cmake
include_guard(GLOBAL) 
include(${CMAKE_CURRENT_LIST_DIR}/ColorMessage.cmake)

option(ENABLE_ASAN "Enable AddressSanitizer" OFF)
if (ENABLE_ASAN)
    color_message(STATUS cyan "[INFO] AddressSanitizer enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O1")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")
else()
    color_message(STATUS cyan "[INFO] AddressSanitizer disabled (enable with -DENABLE_ASAN=ON)")
endif()
