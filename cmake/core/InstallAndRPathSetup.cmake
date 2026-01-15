# robot_shared/cmake/core/InstallAndRPathSetup.cmake
include_guard(GLOBAL)
include(${CMAKE_CURRENT_LIST_DIR}/ColorMessage.cmake)

# --- 安装路径标准 ---
include(GNUInstallDirs)
color_message(STATUS cyan "[INFO] GNUInstallDirs loaded")

# 禁用 new dtags → 用 RPATH
set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -Wl,--disable-new-dtags"
)

# --- RPATH 设置 ---
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")

color_message(STATUS cyan "[INFO] RPATH configured to $ORIGIN/../lib")

