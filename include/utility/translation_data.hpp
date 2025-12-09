#pragma once
#include <unordered_map>
#include <string>

namespace TranslationData {

// ========================
// English Translation Table
// ========================
static const std::unordered_map<std::string, std::string> EN = {
    {"predefine:current_policy_version",       "System is ready."},
    {"predefine:system_ready",                 "System is ready."},
    {"predefine:robot_initialized",            "Robot initialized successfully."},
    {"predefine:imu_lost",                     "IMU connection lost."},
    {"predefine:motor_error",                  "Motor error detected."},
    {"predefine:teleop_start",                 "Teleoperation started."},
    {"predefine:teleop_stop",                  "Teleoperation stopped."},

    // ------- Added Sentences -------
    {"predefine:create_task_mocap",            "Create task: MocapTask"},
    {"predefine:loading_model",                "Loading model file ... "},
    {"predefine:model_loading_complete",       "Model loading complete!"},
    {"predefine:mocap_task_created",           "MocapTask Created!"},
    {"predefine:waiting_mocap_publisher",      "Waiting for Mocap Publisher ..."},
    {"predefine:found_mocap_publisher",        "Find the Mocap Publisher!"},
    {"predefine:current_active_task",          "Current active task: MocapTask"},
    {"predefine:waiting_connect_robot",        "Waiting to connect to the robot ..."},
    {"predefine:connected_robot_success",      "Successfully connected to the robot."},
    {"predefine:enter_zero_torque",            "Enter zero torque state."},
    {"predefine:waiting_start_signal",         "Waiting for the start signal ..."},
    {"predefine:press_z_exit",                 "Press 'z' to exit keyboard listener."},
    {"predefine:start_signal_received",        "Start signal received."},
    {"predefine:moving_default_position",      "Moving to default position ..."},
    {"predefine:reached_default_position",     "Reached default position."},
    {"predefine:waiting_button_a",             "Waiting for the Button A signal ..."},
    {"predefine:button_a_received",            "Button A signal received."},
    {"predefine:gamepad_x_press",              "Gamepad X on press, set flags to zeros!"},
    {"predefine:gamepad_x_release",            "Gamepad X on release, set flags to ones!"},
    {"predefine:keyboard_listener_terminated", "Keyboard listening thread terminated"},
    {"predefine:robot_disconnected_lowstate_timeout", "Robot disconnected (LowState timeout)!"},
    {"predefine:protection_key_not_found", "WestLake protection key was not found"},
    {"predefine:license_check_failed", "License check failed, exiting ..."},
    {"predefine:protection_key_restored", "WestLake protection key restored."},
    {"predefine:protection_key_lost", "WestLake protection key lost!"},
    {"predefine:license_ok", "License OK, continue running ..."},
    { "predefine:try_deactivate_motion_service", "Try to deactivate the motion control-related service." },
    { "predefine:release_mode_failed", "Failed to switch to Release Mode." },
    { "predefine:release_mode_success", "ReleaseMode succeeded." },
};


// ========================
// Chinese Translation Table
// ========================
static const std::unordered_map<std::string, std::string> ZH = {
    {"predefine:current_policy_version",       "系统已准备就绪。"},
    {"predefine:system_ready",                 "系统已准备就绪。"},
    {"predefine:robot_initialized",            "机器人初始化成功。"},
    {"predefine:imu_lost",                     "IMU 连接丢失。"},
    {"predefine:motor_error",                  "检测到电机异常。"},
    {"predefine:teleop_start",                 "遥操作启动。"},
    {"predefine:teleop_stop",                  "遥操作停止。"},

    // ------- Added Sentences -------
    {"predefine:create_task_mocap",            "创建任务: 身外化身"},
    {"predefine:loading_model",                "模型加载中(时间较长，请耐心等待)..."},
    {"predefine:model_loading_complete",       "模型加载完成!"},
    {"predefine:mocap_task_created",           "身外化身创建完成!"},
    {"predefine:waiting_mocap_publisher",      "正在等待客户端数据..."},
    {"predefine:found_mocap_publisher",        "已收到客户端数据!"},
    {"predefine:current_active_task",          "当前激活任务: 身外化身"},
    {"predefine:waiting_connect_robot",        "正在等待机器人连接..."},
    {"predefine:connected_robot_success",      "机器人成功连接!"},
    {"predefine:enter_zero_torque",            "机器人进入零力矩状态。"},
    {"predefine:waiting_start_signal",         "正在等待启动(start)信号(请按遥控器start按钮)..."},
    {"predefine:press_z_exit",                 "按下键盘'z'键退出键盘监听。"},
    {"predefine:start_signal_received",        "已收到启动(start)信号。"},
    {"predefine:moving_default_position",      "机器人正在移动到启动姿态..."},
    {"predefine:reached_default_position",     "已到达启动姿态。"},
    {"predefine:waiting_btutton_a",            "正在等待按钮 A 信号(请按遥控器A按钮)..."},
    {"predefine:button_a_received",            "已收到按钮 A 信号，启动模型(默认原地模式)!"},
    {"predefine:gamepad_x_press",              "按钮 X 按下，关闭跟随模式!"},
    {"predefine:gamepad_x_release",            "按钮 X 松开，开启跟随模式!"},
    {"predefine:keyboard_listener_terminated", "键盘监听线程已结束。"},
    {"predefine:robot_disconnected_lowstate_timeout", "机器人已断开连接(LowState 超时)!"},
    {"predefine:protection_key_not_found",     "未找到 WestLake 保护密钥。"},
    {"predefine:license_check_failed",         "许可证检查失败，程序即将退出。"},
    {"predefine:protection_key_restored",      "WestLake 保护密钥已恢复。"},
    {"predefine:protection_key_lost",          "WestLake 保护密钥丢失!"},
    {"predefine:license_ok",                   "许可证验证通过，继续运行..."},
    { "predefine:try_deactivate_motion_service", "尝试关闭与运动控制相关的服务。" },
    { "predefine:release_mode_failed",          "切换到调试模式失败。" },
    { "predefine:release_mode_success",         "成功切换到调试模式。" },
};
} // namespace TranslationData


