#pragma once

#include <dds/dds.hpp>
#include <memory>
#include <functional>
#include <thread>
#include <atomic>
#include <chrono>
#include <string>

namespace sber {
namespace robot {

template<typename MSG>
class DdsTopicChannel {
public:
    using Callback = std::function<void(const MSG&)>;

    DdsTopicChannel(
        const dds::domain::DomainParticipant& participant,
        const std::string& topic_name)
        : participant_(participant),
          topic_(participant_, topic_name),
          running_(false)
    {}

    // 发布端：显式传入 QoS
    void CreateWriter(const dds::pub::qos::DataWriterQos& qos)
    {
        writer_ = std::make_shared<dds::pub::DataWriter<MSG>>(
            dds::pub::Publisher(participant_),
            topic_,
            qos);
    }

    // 接收端：保持原来的默认 QoS
    void CreateReader(int /*queue_len*/, Callback callback)
    {
        callback_ = callback;

        reader_ = std::make_shared<dds::sub::DataReader<MSG>>(
            dds::sub::Subscriber(participant_),
            topic_);

        running_ = true;

        recv_thread_ = std::thread([this]() {
            while (running_) {
                try {
                    auto samples = reader_->take();

                    for (auto& sample : samples) {
                        if (sample.info().valid() && callback_) {
                            callback_(sample.data());
                        }
                    }
                }
                catch (...) {
                    // 保留原来的异常处理
                }

                std::this_thread::sleep_for(
                    std::chrono::milliseconds(10));
            }
        });
    }

    bool Write(const MSG& msg)
    {
        if (!writer_) return false;

        writer_->write(msg);
        return true;
    }

    ~DdsTopicChannel()
    {
        running_ = false;

        if (recv_thread_.joinable()) {
            recv_thread_.join();
        }
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
} // namespace sber
