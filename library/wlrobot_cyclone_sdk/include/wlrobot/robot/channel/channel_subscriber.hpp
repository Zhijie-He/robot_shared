#pragma once
#include "channel_factory.hpp"
#include "dds_topic_channel.hpp"
#include <memory>
#include <string>

namespace wlrobot {
namespace robot {

template<typename MSG>
class ChannelSubscriber {
public:
    using StrongCallback = std::function<void(const MSG&)>;     // 强类型
    using RawCallback    = std::function<void(const void*)>;     // 宇树风格 void*

    explicit ChannelSubscriber(const std::string& channel_name)
        : channel_name_(channel_name)
    {}

    // ----------- 支持强类型回调 -----------
    void InitChannel(StrongCallback cb, int queue_len = 0)
    {
        strong_callback_ = cb;

        channel_ptr_ =
            ChannelFactory::Instance()->CreateRecvChannel<MSG>(
                channel_name_,
                [this](const MSG& msg){
                    if (strong_callback_) strong_callback_(msg);

                    if (raw_callback_) raw_callback_((const void*)&msg);
                },
                queue_len);
    }

    // ----------- 支持 raw void* 回调（宇树 SDK 风格） -----------
    void InitChannel(RawCallback cb, int queue_len = 0)
    {
        raw_callback_ = cb;

        channel_ptr_ =
            ChannelFactory::Instance()->CreateRecvChannel<MSG>(
                channel_name_,
                [this](const MSG& msg){
                    if (strong_callback_) strong_callback_(msg);

                    if (raw_callback_) raw_callback_((const void*)&msg);
                },
                queue_len);
    }


private:
    std::string channel_name_;
    std::shared_ptr<DdsTopicChannel<MSG>> channel_ptr_;

    StrongCallback strong_callback_;
    RawCallback raw_callback_;
};

} // namespace robot
} // namespace wlrobot

