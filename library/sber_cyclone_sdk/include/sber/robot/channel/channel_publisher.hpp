#pragma once

#include <string>
#include <memory>
#include "channel_factory.hpp"

namespace sber {
namespace robot {

template<typename MSG>
class ChannelPublisher {
public:
    explicit ChannelPublisher(const std::string& name)
        : channel_name_(name)
    {}

    void InitChannel(
        const dds::pub::qos::DataWriterQos& qos = MakeHalWriterQos())
    {
        channel_ = ChannelFactory::Instance()->CreateSendChannel<MSG>(
            channel_name_,
            qos);
    }

    bool Write(const MSG& msg)
    {
        if (!channel_) return false;

        return channel_->Write(msg);
    }

    void CloseChannel()
    {
        channel_.reset();
    }

    const std::string& GetChannelName() const
    {
        return channel_name_;
    }

private:
    std::string channel_name_;
    std::shared_ptr<DdsTopicChannel<MSG>> channel_;
};

} // namespace robot
} // namespace sber
