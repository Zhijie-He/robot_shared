# robot_shared/cmake/core/CompilerSetup.cmake
include_guard(GLOBAL)
include(${CMAKE_CURRENT_LIST_DIR}/ColorMessage.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wno-deprecated-declarations)

color_message(STATUS cyan "[INFO] C++17 standard configured")

