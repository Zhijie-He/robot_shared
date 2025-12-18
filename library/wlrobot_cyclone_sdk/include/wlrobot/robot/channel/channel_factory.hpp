#pragma once
#include <dds/dds.hpp>
#include "dds_topic_channel.hpp"
#include <memory>
#include <optional>

namespace wlrobot {
namespace robot {

class ChannelFactory {
public:
    static ChannelFactory* Instance() {
        static ChannelFactory inst;
        return &inst;
    }

    void Init(int domain_id = 0) {
        participant_.emplace(domain_id);
    }

    template<typename MSG>
    std::shared_ptr<DdsTopicChannel<MSG>>
    CreateSendChannel(const std::string& topic) {
        auto ch = std::make_shared<DdsTopicChannel<MSG>>(participant_.value(), topic);
        ch->CreateWriter();
        return ch;
    }

    template<typename MSG>
    std::shared_ptr<DdsTopicChannel<MSG>>
    CreateRecvChannel(const std::string& topic,
        typename DdsTopicChannel<MSG>::Callback callback,
        int queue_len = 0)
    {
        auto ch = std::make_shared<DdsTopicChannel<MSG>>(participant_.value(), topic);
        ch->CreateReader(queue_len, callback);
        return ch;
    }

private:
    ChannelFactory() = default;
    std::optional<dds::domain::DomainParticipant> participant_;
};

} // namespace robot
} // namespace wlrobot

