#pragma once
#include <dds/dds.hpp>
#include <memory>
#include <functional>
#include <thread>
#include <atomic>
#include <chrono>

namespace wlrobot {
namespace robot {

template<typename MSG>
class DdsTopicChannel {
public:
    using Callback = std::function<void(const MSG&)>;

    DdsTopicChannel(const dds::domain::DomainParticipant& participant,
                    const std::string& topic_name)
        : participant_(participant),
          topic_(participant_, topic_name),
          running_(false)
    {}

    // ---------------- Writer ----------------
    void CreateWriter() {
        writer_ = std::make_shared<dds::pub::DataWriter<MSG>>(
            dds::pub::Publisher(participant_),
            topic_);
    }

    // ---------------- Reader ----------------
    void CreateReader(int /*queue_len*/, Callback callback) {
        callback_ = callback;

        reader_ = std::make_shared<dds::sub::DataReader<MSG>>(
            dds::sub::Subscriber(participant_),
            topic_);

        running_ = true;

        // ----------- 轮询模式（不抛异常，不崩溃）-----------
        recv_thread_ = std::thread([this]() {
            while (running_) {
                try {
                    auto samples = reader_->take();

                    for (auto &s : samples) {
                        if (s.info().valid() && callback_) {
                            callback_(s.data());
                        }
                    }
                }
                catch (...) {
                    // 忽略异常（防止崩溃）
                }

                // 100 Hz 轮询
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        });
    }

    // ---------------- Write ----------------
    bool Write(const MSG& msg) {
        if (!writer_) return false;
        writer_->write(msg);
        return true;
    }

    // ---------------- Destructor ----------------
    ~DdsTopicChannel() {
        running_ = false;
        if (recv_thread_.joinable())
            recv_thread_.join();
    }

private:
    dds::domain::DomainParticipant participant_;
    dds::topic::Topic<MSG> topic_;

    std::shared_ptr<dds::pub::DataWriter<MSG>> writer_;
    std::shared_ptr<dds::sub::DataReader<MSG>> reader_;

    Callback callback_;

    std::thread recv_thread_;
    std::atomic<bool> running_;
};

} // namespace robot
} // namespace wlrobot

