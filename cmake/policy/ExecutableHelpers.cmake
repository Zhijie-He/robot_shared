# robot_shared/cmake/policy/ExecutableSetup.cmake
include_guard(GLOBAL)
include(${CMAKE_CURRENT_LIST_DIR}/../core/ColorMessage.cmake)

function(add_policy_exec name)
    if(NOT DEFINED SRC_FILES)
        message(FATAL_ERROR "SRC_FILES not defined before calling add_policy_exec(${name})")
    endif()

    add_executable(${name} exec/${name}.cpp ${SRC_FILES})
    target_link_libraries(${name} PRIVATE ${COMMON_LIBS})

    color_message(STATUS cyan "[INFO] Added executable target: ${name}")
endfunction()


