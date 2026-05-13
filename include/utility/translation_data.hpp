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
    {"predefine:waiting_mocap_hands_publisher", "Waiting for Mocap Hand Publisher ..."},
    {"predefine:found_mocap_publisher",        "Find the Mocap Publisher!"},
    {"predefine:waiting_first_mocap_data",     "Waiting for First Mocap Data ..."},
    {"predefine:first_mocap_data_received",    "First Mocap Data Received!"},
    {"predefine:first_mocap_hands_data_received", "First Mocap Hands Data Received!"},
    {"predefine:hand_info_mismatch",           "Hand info mismatch!"},
    {"predefine:current_active_task",          "Current active task: MocapTask"},
    {"predefine:waiting_connect_robot",        "Waiting to connect to the robot ..."},
    {"predefine:connected_robot_success",      "Successfully connected to the robot."},
    {"predefine:enter_zero_torque",            "Enter zero torque state."},
    {"predefine:waiting_start_signal",         "Waiting for the start signal ..."},
    {"predefine:press_z_exit",                 "Press 'z' to exit keyboard listener."},
    {"predefine:start_signal_received",        "Start signal received."},
    {"predefine:moving_hands_to_close_position", "Moving hands to fist pose ..."},
    {"predefine:moving_default_position",      "Moving to default position ..."},
    {"predefine:moving_crouch_position",       "Moving to crouch position ..."},
    {"predefine:moving_zero_position",         "Moving to zero position ..."},
    {"predefine:hands_reached_close_position", "Hands reached fist pose."},
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
    {"predefine:interface_not_found",           "interface not found, retrying in 2 seconds..." },
    {"predefine:model_not_running",             "Model process not running" },
    {"predefine:model_pid_invalid",             "Model PID invalid, no process found" },
    {"predefine:lowstate_crc_error",            "Lowstate CRC Error" },
    {"predefine:no_mocap_data_available",       "No mocap data available, exiting!" },
    {"predefine:no_mocap_hand_data_available",  "No mocap hand data available, exiting!" },
    {"predefine:obs_contains_nan_or_inf",       "Observation contains nan or inf! Abort." },
    {"predefine:failed_create_dds_participant", "Failed to create DDS participant." },
    {"predefine:failed_create_dds_topic",       "Failed to create DDS topic." },
    {"predefine:failed_create_dds_reader",      "Failed to create DDS reader." }, 
    {"predefine:failed_find_mocap_data",        "Failed to find mocap data, exiting..." }, 
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
    {"predefine:waiting_mocap_hands_publisher", "正在等待客户端手部数据发布服务..."},
    {"predefine:found_mocap_publisher",        "已发现客户端数据发布服务!"},
    {"predefine:waiting_first_mocap_data",     "正在等待客户端数据"},
    {"predefine:first_mocap_data_received",    "已收到客户端数据！"},
    {"predefine:first_mocap_hands_data_received", "已收到手部数据！"},
    {"predefine:hand_info_mismatch",           "手部数据不匹配！"},
    {"predefine:current_active_task",          "当前激活任务: 身外化身"},
    {"predefine:waiting_connect_robot",        "正在等待机器人连接..."},
    {"predefine:connected_robot_success",      "机器人成功连接!"},
    {"predefine:enter_zero_torque",            "机器人进入零力矩状态。"},
    {"predefine:waiting_start_signal",         "正在等待启动(start)信号(请按遥控器start按钮)..."},
    {"predefine:press_z_exit",                 "按下键盘'z'键退出键盘监听。"},
    {"predefine:start_signal_received",        "已收到启动(start)信号。"},
    {"predefine:moving_hands_to_close_position", "手部移动到握拳状态..."},
    {"predefine:moving_default_position",      "机器人正在移动到启动姿态..."},
    {"predefine:moving_crouch_position",       "机器人正在移动到蹲伏姿态..."},
    {"predefine:moving_zero_position",         "机器人正在移动到零力矩姿态..."},
    {"predefine:hands_reached_close_position",  "已到达握拳姿态。"},
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
    {"predefine:interface_not_found",           "未找到网络接口，2 秒后重试……"},
    {"predefine:model_not_running",             "模型进程未运行"},
    {"predefine:model_pid_invalid",             "模型 PID 无效，未找到对应进程"},
    {"predefine:lowstate_crc_error",            "Lowstate CRC 校验错误"},
    {"predefine:no_mocap_data_available",       "没有可用的mocap数据，退出程序……" },
    {"predefine:no_mocap_hand_data_available",  "没有可用的手部数据，退出程序……" },
    {"predefine:obs_contains_nan_or_inf",       "状态值包含 NaN 或 Inf，已中止。"},
    {"predefine:failed_create_dds_participant", "创建 DDS Participant 失败。"},
    {"predefine:failed_create_dds_topic",       "创建 DDS Topic 失败。"},
    {"predefine:failed_create_dds_reader",      "创建 DDS Reader 失败。"},
    {"predefine:failed_find_mocap_data",        "未发现mocap的发布器，退出程序……" }, 
    {"predefine:failed_receive_lowstate",       "未接受到机器人状态数据，退出程序……" }, 
};

// ========================
// English Translation Sub Table
// ========================
static const std::unordered_map<std::string, std::string> SUB_EN = {
    {"predefine:kill_model",                    "Kill Model! at "},
    {"predefine:zero_stop",                     "Safety Stop! at "},
    {"predefine:crouch_stop",                   "Crouch Stop! at "},
    {"predefine:unknown_encryption_error",      "Unknown encryption error: "},
    {"predefine:encryption_error",              "Encryption error: "},
    {"predefine:failed_get_program_path",       "Failed to get program path: "},
    {"predefine:unable_open_CycloneDDS_file",   "Unable to open CycloneDDS file: "},
    {"predefine:unable_write_CycloneDDS_file",  "Unable to write CycloneDDS file: "},
    {"predefine:failed_open_json_file",         "[Failed to open JSON file: "},
    {"predefine:failed_load_model",             "Failed to load model: "},
    {"predefine:load_xml_model_error",          "Load xml model error: "}, 
    {"predefine:failed_create_inference_engine","Failed to create inference engine: "},
    {"predefine:unknown_robot_backend_type",    "Unknown robot backend type: "},
    {"predefine:unknown_hands_backend_type",    "Unknown hands type: "},
    {"predefine:config_file_not_found",         "Config file not found: "},
    {"predefine:inference_info",                ""},
    {"predefine:inference_late_time",           ""},
};

// ========================
// Chinese Translation Sub Table
// ========================
static const std::unordered_map<std::string, std::string> SUB_ZH = {
    {"predefine:kill_model",                    "杀死模型，位于 "},
    {"predefine:zero_stop",                     "安全停止，位于 "},
    {"predefine:crouch_stop",                   "蹲伏停止，位于 "},
    {"predefine:unknown_encryption_error",      "未知的加密错误："},
    {"predefine:encryption_error",              "加密错误："},
    {"predefine:failed_get_program_path",       "获取程序路径失败："},
    {"predefine:unable_open_CycloneDDS_file",   "无法打开 CycloneDDS 文件："},
    {"predefine:unable_write_CycloneDDS_file",  "无法写入 CycloneDDS 文件："},
    {"predefine:failed_open_json_file",         "打开 JSON 文件失败："},
    {"predefine:failed_load_model",             "[加载模型失败："},
    {"predefine:load_xml_model_error",          "加载 XML 模型错误："},
    {"predefine:failed_create_inference_engine","创建推理类型失败："},
    {"predefine:unknown_robot_backend_type",    "未知的机器人类型："},
    {"predefine:unknown_hands_backend_type",    "未知的手部类型："},
    {"predefine:config_file_not_found",         "配置文件未找到："},
    {"predefine:inference_info",                ""},
    {"predefine:inference_late_time",           ""},
};

// ========================
// Marker Code Table
// 0x63或6011是指令回传客户端
// 60100000-60100099 外设错误; 
//      0-9 加密狗; 10-19 网络问题;  20-29 指令输入问题;  //30-39 机器人和动捕输入数据问题； 
// 60100100-60100199 加载文件丢失或者错误;  
// 60100200-60100299 代码加载逻辑问题;
// ========================
static const std::unordered_map<std::string, std::string> MARKER_CODE = {
    // ------- Response Code ------
    {"predefine:waiting_start_signal",                  "[0x630000]"},  // 标记model加载完成，等待start信号
    {"predefine:press_z_exit",                          "[0x630000]"},
    {"predefine:start_signal_received",                 "[60110000]"},
    {"predefine:button_a_received",                     "[60110001]"},
    {"predefine:gamepad_x_press",                       "[60110002]"},
    {"predefine:gamepad_x_release",                     "[60110003]"},
    {"predefine:hold_position_active",                  "[60110002]"},
    {"predefine:release_position_active",               "[60110003]"},

    // ------- ErrorCode ------
    {"predefine:license_check_failed",                  "[60100000]"},  // 问题：未检测到加密狗              //解决办法：重插加密狗
    {"predefine:robot_disconnected_lowstate_timeout",   "[60100030]"},  // 问题：机器人断开连接              //解决办法：重启机器人，检查机器人硬件通信
    {"predefine:protection_key_lost",                   "[60100003]"},  // 问题：加密狗丢失                 //解决办法：重插加密狗
    {"predefine:interface_not_found",                   "[60100010]"},  // 问题：wifi接口没有发现           //解决办法：检查有线和无线网卡
    {"predefine:lowstate_crc_error",                    "[60100031]"},  // 问题：机器人机器人状态数据CRC异常  //解决办法：重启模型
    {"predefine:no_mocap_data_available",               "[60100032]"},  // 问题：未发现客户端数据            //解决办法：检查客户端的数据是否异常
    {"predefine:failed_find_mocap_data",                "[60100033]"},  // 问题：未发现客户端数据            //解决办法：检查客户端的数据是否异常
    {"predefine:failed_receive_lowstate",               "[60100035]"},  // 问题：未发现机器人状态数据         //解决办法：重启机器人，检查机器人硬件通信
    {"predefine:obs_contains_nan_or_inf",               "[60100200]"},  // 问题：模型推理数据异常            //解决办法：重新启动模型
    {"predefine:failed_create_dds_participant",         "[60100201]"},  // 问题：创建dds通信失败            //解决办法：检查网络连接和dds服务，然后重启机器人
    {"predefine:failed_create_dds_topic",               "[60100201]"},  // 问题：创建dds通信失败            //解决办法：检查网络连接和dds服务，然后重启机器人
    {"predefine:failed_create_dds_reader",              "[60100201]"},  // 问题：创建dds通信失败            //解决办法：检查网络连接和dds服务，然后重启机器人
};

// ========================
// Sub Marker Code Table
// ========================
static const std::unordered_map<std::string, std::string> SUB_MARKER_CODE = {
    // ------- Response Code ------
    {"predefine:kill_model",                            "[60110004]"}, // 标记正常杀死模型
    {"predefine:zero_stop",                             "[60110005]"}, // 标记GAE紧急停止
    {"predefine:crouch_stop",                           "[60110006]"}, // 标记GAE蹲伏停止
    {"predefine:inference_info",                        "[60110010]"},

    // ------- ErrorCode ------
    {"predefine:unknown_encryption_error",              "[60100003]"},  // 问题：加密狗错误                     //解决办法：重插加密狗
    {"predefine:encryption_error",                      "[60100003]"},  // 问题：加密狗错误                     //解决办法：重插加密狗
    {"predefine:failed_get_program_path",               "[60100100]"},  // 问题：失败获取当前脚本文件路径         //解决办法：检查脚本文件执行权限、文件是否存在及相关问题
    {"predefine:unable_open_CycloneDDS_file",           "[60100101]"},  // 问题：失败打开cyclonedds.xml文件     //解决办法：检查文件执行权限、文件是否存在及相关问题
    {"predefine:unable_write_CycloneDDS_file",          "[60100102]"},  // 问题：失败写入cyclonedds.xml文件     //解决办法：检查文件执行权限、文件是否存在及相关问题
    {"predefine:failed_open_json_file",                 "[60100103]"},  // 问题：失败打开teleopTask.josn文件    //解决办法：检查teleopTask.josn文件执行权限、文件是否存在及相关问题
    {"predefine:failed_load_model",                     "[60100104]"},  // 问题：失败加载model.engine文件       //解决办法：检查model.engine文件执行权限、文件是否存在及相关问题
    {"predefine:load_xml_model_error",                  "[60100105]"},  // 问题：加载的model的xml文件有问题     // 解决办法：检查机器人的model的xml文件执行权限、文件是否存在及相关问题
    {"predefine:config_file_not_found",                 "[60100106]"},  // 问题：yaml配置文件未找到             //解决办法：检查配置文件是否存在及相关问题
    {"predefine:failed_create_inference_engine",        "[60100204]"},  // 问题：失败创建tensorrt模型推理器     // 解决办法：检查本地是否有tensorrt库
    {"predefine:unknown_robot_backend_type",            "[60100205]"},  // 问题：未知的机器人类型               // 解决办法：检查机器人参数是否输入正确
    {"predefine:inference_late_time",                   "[60100206]"},  // 问题：产生推理延迟                   //解决办法：清除不必要的进程占用或者重新启动机器人
};
} // namespace TranslationData