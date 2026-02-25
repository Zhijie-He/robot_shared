# robot_shared/cmake/policy/ExecutableHelpers.cmake
include_guard(GLOBAL)
include(${CMAKE_CURRENT_LIST_DIR}/../core/ColorMessage.cmake)

function(add_policy_exec name)
    if(NOT DEFINED SRC_FILES)
        message(FATAL_ERROR "SRC_FILES not defined before calling add_policy_exec(${name})")
    endif()

    # ---- optional exec path (minimal change) ----
    # usage:
    #   add_policy_exec(foo)          -> exec/foo.cpp
    #   add_policy_exec(foo tools)    -> tools/foo.cpp
    if(ARGC GREATER 1)
        set(exec_path "${ARGV1}")
    else()
        set(exec_path "exec")
    endif()

    add_executable(${name} ${exec_path}/${name}.cpp $<TARGET_OBJECTS:common_obj>)
    target_link_libraries(${name} PRIVATE ${COMMON_LIBS})

    color_message(STATUS cyan "[INFO] Added executable target: ${name} (path=${exec_path})")
endfunction()