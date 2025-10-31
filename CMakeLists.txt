# ========== robot_shared utility (header-only) ==========
if(USE_UTILITY)
add_library(robot_shared_utility INTERFACE)
target_include_directories(robot_shared_utility INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
endif()

# ========== Eigen (header-only) ==========
if(USE_EIGEN)
add_library(robot_shared_eigen INTERFACE)
target_include_directories(robot_shared_eigen INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/library/Eigen
)
endif()

# ========== Mujoco ==========
if(USE_MUJOCO)
add_library(robot_shared_mujoco INTERFACE)
target_include_directories(robot_shared_mujoco INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/library/mujoco/include
)
target_link_directories(robot_shared_mujoco INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/library/mujoco/lib/${CURRENT_PLATFORM}
)
target_link_libraries(robot_shared_mujoco INTERFACE mujoco)
endif()

# ========== CycloneDDS(Unitree SDK2) ==========
if(USE_CYCLONEDDS)
add_library(robot_shared_cyclonedds INTERFACE)
target_include_directories(robot_shared_cyclonedds INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/library/unitree_sdk2/thirdparty/include
    ${CMAKE_CURRENT_SOURCE_DIR}/library/unitree_sdk2/thirdparty/include/ddscxx
)
target_link_directories(robot_shared_cyclonedds INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/library/unitree_sdk2/thirdparty/lib/${CMAKE_SYSTEM_PROCESSOR}
)
target_link_libraries(robot_shared_cyclonedds INTERFACE ddscxx ddsc)
endif()

# ========== FastDDS ==========
if(USE_FASTDDS)
add_library(robot_shared_fastdds INTERFACE)
target_include_directories(robot_shared_fastdds INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/library/fastdds/include
)
target_link_directories(robot_shared_fastdds INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/library/fastdds/lib/${CMAKE_SYSTEM_PROCESSOR}
)
target_link_libraries(robot_shared_fastdds INTERFACE fastdds fastcdr)
endif()

# ========== Unitree SDK2 ==========
if(USE_UNITREESDK2)
add_library(robot_shared_unitree_sdk2 INTERFACE)
target_include_directories(robot_shared_unitree_sdk2 INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/library/unitree_sdk2/include
)
target_link_directories(robot_shared_unitree_sdk2 INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/library/unitree_sdk2/lib/${CMAKE_SYSTEM_PROCESSOR}
)
target_link_libraries(robot_shared_unitree_sdk2 INTERFACE unitree_sdk2)
endif()

# ========== Westlake Cyclone SDK ==========
if(USE_WLCYCLONEDDSSDK)
add_library(robot_shared_westlake_cyclonedds_sdk INTERFACE)
target_include_directories(robot_shared_westlake_cyclonedds_sdk INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/library/wlrobot_cyclone_sdk/include
)
endif()

# ========== Westlake fastdds SDK ==========
if(USE_WLFASTDDSSDK)
file(GLOB_RECURSE WESTLAKE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/library/wlrobot_fast_sdk/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/library/wlrobot_fast_sdk/src/*.c
)
add_library(robot_shared_westlake_fastdds_sdk STATIC ${WESTLAKE_SOURCES})
target_include_directories(robot_shared_westlake_fastdds_sdk PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/library/wlrobot_fast_sdk/include
)
target_link_libraries(robot_shared_westlake_fastdds_sdk PRIVATE robot_shared_fastdds)
endif()

# ========== Hasp Encryption SDK ==========
if(USE_ENCRYPTION)
file(GLOB_RECURSE HASP_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/library/hasp/src/*.cpp
)
add_library(robot_shared_encryption STATIC ${HASP_SOURCES})
target_include_directories(robot_shared_encryption PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/library/hasp/include
)
target_link_directories(robot_shared_encryption PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/library/hasp/lib/${CMAKE_SYSTEM_PROCESSOR}
)
target_link_libraries(robot_shared_encryption PRIVATE
    hasp_cpp
    hasp_36478
    pthread
)
endif()

# ========== YAML ==========
if(USE_YAML)
add_library(robot_shared_yaml INTERFACE)
target_include_directories(robot_shared_yaml INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/library/yaml/include
)
target_link_directories(robot_shared_yaml INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/library/yaml/lib/${CMAKE_SYSTEM_PROCESSOR}
)
target_link_libraries(robot_shared_yaml INTERFACE yaml-cpp)
endif()
