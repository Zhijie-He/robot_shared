#pragma once

#include <dds/dds.hpp>
#include "dds_topic_channel.hpp"

#include <memory>
#include <optional>
#include <string>

namespace sber {
namespace robot {

// Sber HAL default publisher qos setting
inline dds::pub::qos::DataWriterQos MakeHalWriterQos()
{
    dds::pub::qos::DataWriterQos qos;

    qos << dds::core::policy::Reliability::BestEffort()
        << dds::core::policy::Durability::Volatile()
        << dds::core::policy::History::KeepLast(1)
        << dds::core::policy::Deadline(dds::core::Duration(0, 500000000))
        << dds::core::policy::Liveliness::Automatic();

    return qos;
}

class ChannelFactory {
public:
    static ChannelFactory* Instance()
    {
        static ChannelFactory instance;
        return &instance;
    }

    void Init(int domain_id = 0)
    {
        participant_.emplace(domain_id);
    }

    template<typename MSG>
    std::shared_ptr<DdsTopicChannel<MSG>>
    CreateSendChannel(
        const std::string& topic,
        const dds::pub::qos::DataWriterQos& qos = MakeHalWriterQos())
    {
        auto channel = std::make_shared<DdsTopicChannel<MSG>>(
            participant_.value(),
            topic);

        channel->CreateWriter(qos);

        return channel;
    }

    template<typename MSG>
    std::shared_ptr<DdsTopicChannel<MSG>>
    CreateRecvChannel(
        const std::string& topic,
        typename DdsTopicChannel<MSG>::Callback callback,
        int queue_len = 0)
    {
        auto channel = std::make_shared<DdsTopicChannel<MSG>>(
            participant_.value(),
            topic);

        channel->CreateReader(queue_len, callback);

        return channel;
    }

private:
    ChannelFactory() = default;

    std::optional<dds::domain::DomainParticipant> participant_;
};

} // namespace robot
} // namespace sber
