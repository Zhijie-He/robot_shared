#pragma once
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>

#include "hasp_api_cpp.h"
#include "vendor_code.h"
#include "errorprinter.h"

class HaspWatcher {
public:
    static HaspWatcher& instance() {
        static HaspWatcher instance;
        return instance;
    }

    bool start() {
        if (running_) return true; 

        ChaspFeature haspFeature = ChaspFeature::fromFeature(feature_);
        hasp_ = std::make_unique<Chasp>(haspFeature);
        hasp_->config((hasp_vendor_code_t)vendorCode, config_);
        status_ = hasp_->login((hasp_vendor_code_t)vendorCode, scope_);

        if (!HASP_SUCCEEDED(status_)) {
            // std::cerr << "[HaspWatcher] Login failed, status=0x"
            //           << std::hex << status_ << std::endl;
            // FRC_ERROR("[HaspWatcher.start] Login failed, status=0x");
            errorPrinter_.printError(status_);
            return false;
        }

        license_valid_ = true;
        running_ = true;
        worker_ = std::thread(&HaspWatcher::monitorLoop, this);
        return true;
    }

    void stop() {
        running_ = false;
        if (worker_.joinable()) worker_.join();
        if (hasp_) hasp_->logout();
    }

    bool isLicenseValid() const { return license_valid_.load(); }

    // 禁止复制与拷贝
    HaspWatcher(const HaspWatcher&) = delete;
    HaspWatcher& operator=(const HaspWatcher&) = delete;

private:
    HaspWatcher()
        : config_(notUseAuthRuntimeConfig),
          feature_(CUSTOM_FEATURE_1),
          scope_(localScope),
          running_(false),
          license_valid_(false) {}

    ~HaspWatcher() { stop(); }

    void monitorLoop() {
        while (running_) {
            std::this_thread::sleep_for(std::chrono::seconds(3));

            std::string info;
            // status_ = hasp_->getSessionInfo(Chasp::keyInfo(), info);
            const char* testscope = "<haspscope />\n";
            const char* format = "<haspformat root=\"my_custom_scope\">\n"
                        "  <hasp>\n"
                        "    <attribute name=\"id\" />\n"
                        "  </hasp>\n"
                        "</haspformat>\n";
                        
            Chasp test;
            status_ = test.getInfo(testscope, format, (hasp_vendor_code_t)vendorCode, info);

            if (HASP_SUCCEEDED(status_)) {
                if (!license_valid_) {
                    // std::cout << "[HaspWatcher] License restored.\n";
                    FRC_HIGHLIGHT("[HaspWatcher.monitorLoop] WestLake protection key restored.");
                    license_valid_ = true;
                }
            } else {
                // if (license_valid_) {
                    // std::cerr << "[HaspWatcher] License lost! status=0x"
                    //           << std::hex << status_ << std::endl;
                    FRC_WARN("[HaspWatcher.monitorLoop] WestLake protection key lost!");
                    // errorPrinter_.printError(status_);
                    license_valid_ = false;
                // }
            }
        }
    }

private:
    // config 定义
    const char *useAuthRuntimeConfig =
        "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
        "  <haspconfig>"
        "    <auth_config>"
        "      <hasp_auth_rte>1</hasp_auth_rte>"
        "    </auth_config>"
        "  </haspconfig>";

    const char *notUseAuthRuntimeConfig =
        "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
        "  <haspconfig>"
        "    <auth_config>"
        "      <hasp_auth_rte>0</hasp_auth_rte>"
        "    </auth_config>"
        "  </haspconfig>";

    // scope 定义
    const char *localScope =
        "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
        "  <haspscope>"
        "    <license_manager hostname=\"localhost\" />"
        "  </haspscope>";

    const char *nonCLScope =
        "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
        "  <haspscope>"
        "    <hasp cloud_originated=\"false\" ></hasp>"
        "  </haspscope>";

    const char *CLScope =
        "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
        "  <haspscope>"
        "    <hasp cloud_originated=\"true\" ></hasp>"
        "  </haspscope>";

    // 内部状态
    const hasp_u32_t CUSTOM_FEATURE_1 = 1;
    hasp_u32_t feature_;
    const char *config_;
    const char *scope_;
    haspStatus status_;
    ErrorPrinter errorPrinter_;

    std::unique_ptr<Chasp> hasp_;
    std::atomic<bool> running_;
    std::atomic<bool> license_valid_;
    std::thread worker_;
};

