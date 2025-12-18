#pragma once
#include <string>
#include <memory>
#include "channel_factory.hpp"

namespace wlrobot {
namespace robot {

template<typename MSG>
class ChannelPublisher {
public:
    explicit ChannelPublisher(const std::string& name)
        : channel_name_(name)
    {}

    void InitChannel() {
        channel_ = ChannelFactory::Instance()->CreateSendChannel<MSG>(channel_name_);
    }

    bool Write(const MSG& msg) {
        if (!channel_) return false;
        return channel_->Write(msg);
    }

    const std::string& GetChannelName() const {
        return channel_name_;
    }

private:
    std::string channel_name_;
    std::shared_ptr<DdsTopicChannel<MSG>> channel_;
};

} // namespace robot
} // namespace wlrobot

