#pragma once

#include "channel_factory.hpp"
#include "dds_topic_channel.hpp"

#include <functional>
#include <memory>
#include <string>

namespace sber {
namespace robot {

template<typename MSG>
class ChannelSubscriber {
public:
    using StrongCallback = std::function<void(const MSG&)>;
    using RawCallback = std::function<void(const void*)>;

    explicit ChannelSubscriber(const std::string& channel_name)
        : channel_name_(channel_name)
    {}

    // 强类型回调
    void InitChannel(StrongCallback callback, int queue_len = 0)
    {
        channel_ptr_ =
            ChannelFactory::Instance()->CreateRecvChannel<MSG>(
                channel_name_,
                callback,
                queue_len);
    }

    // 宇树风格 const void* 回调
    void InitChannel(RawCallback callback, int queue_len = 0)
    {
        channel_ptr_ =
            ChannelFactory::Instance()->CreateRecvChannel<MSG>(
                channel_name_,
                [callback](const MSG& msg) {
                    if (callback) {
                        callback(static_cast<const void*>(&msg));
                    }
                },
                queue_len);
    }

private:
    std::string channel_name_;
    std::shared_ptr<DdsTopicChannel<MSG>> channel_ptr_;
};

} // namespace robot
} // namespace sber
