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
    {"predefine:waiting_first_mocap_data",     "Waiting for First Mocap Data ..."},
    {"predefine:first_mocap_data_received",    "First Mocap Data Received!"},
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
    {"predefine:hold_position_active",         "Hold position active, The robot cannot move or turn!"},
    {"predefine:release_position_active",      "Release position active, The robot can move or turn!"},
    {"predefine:keyboard_listener_terminated",  "Keyboard listening thread terminated"},
    {"predefine:robot_disconnected_lowstate_timeout",   "Robot disconnected (LowState timeout)!"},
    {"predefine:protection_key_not_found",      "WestLake protection key was not found"},
    {"predefine:license_check_failed",          "License check failed, exiting ..."},
    {"predefine:protection_key_restored",       "WestLake protection key restored."},
    {"predefine:protection_key_lost",           "WestLake protection key lost!"},
    {"predefine:license_ok",                    "License OK, continue running ..."},
    {"predefine:try_deactivate_motion_service", "Try to deactivate the motion control-related service." },
    {"predefine:release_mode_failed",           "Failed to switch to Release Mode." },
    {"predefine:release_mode_success",          "ReleaseMode succeeded." },
    {"predefine:wifi_interface_not_found",      "Wi-Fi interface not found, retrying in 2 seconds..." },
    {"predefine:model_not_running",             "Model process not running" },
    {"predefine:model_pid_invalid",             "Model PID invalid, no process found" },
    {"predefine:lowstate_crc_error",            "Lowstate CRC Error" },
    {"predefine:no_new_mocap_message",          "No new message, use last message" },
    {"predefine:obs_contains_nan_or_inf",       "Observation contains nan or inf! Abort." },
    {"predefine:failed_create_dds_participant", "Failed to create DDS participant." },
    {"predefine:failed_create_dds_topic",       "Failed to create DDS topic." },
    {"predefine:failed_create_dds_reader",      "Failed to create DDS reader." }, 
    {"predefine:failed_find_mocap_publisher",   "Failed to find mocap publisehr, exiting..." }, 
    {"predefine:no_received_mocap_data",        "No received mocap data, exiting..." }, 
    {"predefine:failed_receive_lowstate",       "Failed to receive lowstate, exiting..." }, 
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
    {"predefine:waiting_mocap_publisher",      "正在等待客户端数据发布服务..."},
    {"predefine:found_mocap_publisher",        "已发现客户端数据发布服务!"},
    {"predefine:waiting_first_mocap_data",     "正在等待客户端数据"},
    {"predefine:first_mocap_data_received",    "已收到客户端数据！"},
    {"predefine:current_active_task",          "当前激活任务: 身外化身"},
    {"predefine:waiting_connect_robot",        "正在等待机器人连接..."},
    {"predefine:connected_robot_success",      "机器人成功连接!"},
    {"predefine:enter_zero_torque",            "机器人进入零力矩状态。"},
    {"predefine:waiting_start_signal",         "正在等待启动(start)信号(请按遥控器start按钮)..."},
    {"predefine:press_z_exit",                 "按下键盘'z'键退出键盘监听。"},
    {"predefine:start_signal_received",        "已收到启动(start)信号。"},
    {"predefine:moving_default_position",      "机器人正在移动到启动姿态..."},
    {"predefine:reached_default_position",     "已到达启动姿态。"},
    {"predefine:waiting_button_a",             "正在等待按钮 A 信号(请按遥控器A按钮)..."},
    {"predefine:button_a_received",            "已收到按钮 A 信号，启动模型(默认原地模式)!"},
    {"predefine:gamepad_x_press",              "按钮 X 按下，开启原地模式, 机器人不能位移和转向!"},
    {"predefine:gamepad_x_release",            "按钮 X 松开，开启跟随模式, 机器人可以位移和转向!"},
    {"predefine:hold_position_active",         "开启原地模式, 机器人不能位移和转向!"},
    {"predefine:release_position_active",      "开启跟随模式, 机器人可以位移和转向!"},
    {"predefine:keyboard_listener_terminated", "键盘监听线程已结束。"},
    {"predefine:robot_disconnected_lowstate_timeout", "机器人已断开连接(LowState 超时)!"},
    {"predefine:protection_key_not_found",     "未找到 WestLake 保护密钥。"},
    {"predefine:license_check_failed",         "许可证检查失败，程序即将退出。"},
    {"predefine:protection_key_restored",      "WestLake 保护密钥已恢复。"},
    {"predefine:protection_key_lost",          "WestLake 保护密钥丢失!"},
    {"predefine:license_ok",                   "许可证验证通过，继续运行..."},
    {"predefine:try_deactivate_motion_service",     "尝试关闭与运动控制相关的服务。" },
    {"predefine:release_mode_failed",           "切换到调试模式失败。" },
    {"predefine:release_mode_success",          "成功切换到调试模式。" },
    {"predefine:wifi_interface_not_found",      "未找到 Wi-Fi 接口，2 秒后重试……"},
    {"predefine:model_not_running",             "模型进程未运行"},
    {"predefine:model_pid_invalid",             "模型 PID 无效，未找到对应进程"},
    {"predefine:lowstate_crc_error",            "Lowstate CRC 校验错误"},
    {"predefine:no_new_mocap_message",          "未收到新的消息，使用上一条消息"},
    {"predefine:obs_contains_nan_or_inf",       "状态值包含 NaN 或 Inf，已中止。"},
    {"predefine:failed_create_dds_participant", "创建 DDS Participant 失败。"},
    {"predefine:failed_create_dds_topic",       "创建 DDS Topic 失败。"},
    {"predefine:failed_create_dds_reader",      "创建 DDS Reader 失败。"},
    {"predefine:failed_find_mocap_publisher",   "未发现mocap的发布器，退出程序……" }, 
    {"predefine:no_received_mocap_data",        "未接受到mocap数据，退出程序……" }, 
    {"predefine:failed_receive_lowstate",       "未接受到机器人状态数据，退出程序……" }, 
};

// ========================
// English Translation Sub Table
// ========================
static const std::unordered_map<std::string, std::string> SUB_EN = {
    {"predefine:emergency_stop",      "Emergency Stop! at "},
    {"predefine:unknown_encryption_error",      "Unknown encryption error: "},
    {"predefine:encryption_error",              "Encryption error: "},
    {"predefine:failed_get_program_path",       "Failed to get program path: "},
    {"predefine:unable_open_CycloneDDS_file",   "Unable to open CycloneDDS file: "},
    {"predefine:unable_write_CycloneDDS_file",  "Unable to write CycloneDDS file: "},
    {"predefine:failed_open_json_file",         "[Failed to open JSON file: "},
    {"predefine:failed_load_model",             "Failed to load model: "},
    {"predefine:load_xml_model_error",          "Load xml model error: "}, 
    {"predefine:failed_create_inference_engine",    "Failed to create inference engine: "},
    {"predefine:unknown_robot_backend_type",    "Unknown robot backend type: "},
    {"predefine:inference_info",                ""},
};

// ========================
// Chinese Translation Sub Table
// ========================
static const std::unordered_map<std::string, std::string> SUB_ZH = {
    {"predefine:emergency_stop",                "紧急停止，位于 "},
    {"predefine:unknown_encryption_error",      "未知的加密错误："},
    {"predefine:encryption_error",              "加密错误："},
    {"predefine:failed_get_program_path",       "获取程序路径失败："},
    {"predefine:unable_open_CycloneDDS_file",   "无法打开 CycloneDDS 文件："},
    {"predefine:unable_write_CycloneDDS_file",  "无法写入 CycloneDDS 文件："},
    {"predefine:failed_open_json_file",         "打开 JSON 文件失败："},
    {"predefine:failed_load_model",             "[加载模型失败："},
    {"predefine:load_xml_model_error",          "加载 XML 模型错误："},
    {"predefine:failed_create_inference_engine",    "创建推理类型失败："},
    {"predefine:unknown_robot_backend_type",    "未知的机器人类型："},
    {"predefine:inference_info",                ""},
};

// ========================
// Marker Code Table
// 0x600000-0x600099 外设错误; 
//      0-9 加密狗; 10-19 网络问题;  20-29 指令输入问题;  //30-39 机器人和动捕输入数据问题； 
// 0x600100-0x600199 加载文件丢失或者错误;  
// 0x600200-0x600299 代码加载逻辑问题;
// ========================
static const std::unordered_map<std::string, std::string> MARKER_CODE = {
    // ------- Response Code ------
    {"predefine:waiting_start_signal",                  "[0x630000]"},
    {"predefine:start_signal_received",                 "[0x610000]"},
    {"predefine:button_a_received",                     "[0x610001]"},
    {"predefine:gamepad_x_press",                       "[0x610002]"},
    {"predefine:gamepad_x_release",                     "[0x610003]"},
    {"predefine:hold_position_active",                  "[0x610002]"},
    {"predefine:release_position_active",               "[0x610003]"},
    
    // ------- ErrorCode ------
    {"predefine:license_check_failed",                  "[0x600000]"},
    {"predefine:robot_disconnected_lowstate_timeout",   "[0x600030]"},
    {"predefine:protection_key_lost",                   "[0x600003]"},
    {"predefine:wifi_interface_not_found",              "[0x600010]"},
    {"predefine:model_not_running",                     "[0x600021]"},
    {"predefine:model_pid_invalid",                     "[0x600022]"},
    {"predefine:lowstate_crc_error",                    "[0x600031]"},
    {"predefine:no_new_mocap_message",                  "[0x600032]"},
    {"predefine:failed_find_mocap_publisher",           "[0x600033]"}, 
    {"predefine:no_received_mocap_data",                "[0x600034]"}, 
    {"predefine:failed_receive_lowstate",               "[0x600035]"}, 
    {"predefine:obs_contains_nan_or_inf",               "[0x600200]"},  // 问题：模型推理数据异常//解决办法：重新启动模型
    {"predefine:failed_create_dds_participant",         "[0x600201]"},  // 问题：创建dds通信失败 //解决办法：检查网络连接和dds服务
    {"predefine:failed_create_dds_topic",               "[0x600201]"},  // 问题：创建dds通信失败 //解决办法：检查网络连接和dds服务
    {"predefine:failed_create_dds_reader",              "[0x600201]"},  // 问题：创建dds通信失败 //解决办法：检查网络连接和dds服务
};

// ========================
// Sub Marker Code Table
// ========================
static const std::unordered_map<std::string, std::string> SUB_MARKER_CODE = {
    // ------- Response Code ------
    {"predefine:emergency_stop",                        "[0x610005]"},
    {"predefine:inference_info",                        "[0x610010]"},

    // ------- ErrorCode ------
    {"predefine:unknown_encryption_error",              "[0x600001]"},
    {"predefine:encryption_error",                      "[0x600002]"},
    {"predefine:failed_get_program_path",               "[0x600100]"},
    {"predefine:unable_open_CycloneDDS_file",           "[0x600101]"},
    {"predefine:unable_write_CycloneDDS_file",          "[0x600102]"},
    {"predefine:failed_open_json_file",                 "[0x600103]"},
    {"predefine:failed_load_model",                     "[0x600104]"},
    {"predefine:load_xml_model_error",                  "[0x600105]"},  // 问题：加载的xml文件有问题  // 解决办法：检查机器人的xml文件
    {"predefine:failed_create_inference_engine",        "[0x600204]"},
    {"predefine:unknown_robot_backend_type",            "[0x600205]"},
    {"predefine:inference_late_time",                   "[0x600206]"},  // 问题：产生推理延迟 //解决办法：清除不必要的进程占用或者重新启动机器人
};
} // namespace TranslationData