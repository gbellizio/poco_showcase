//
// Created by gennaro on 25/11/20.
//

#include "logging/priority_channel.h"
#include <Poco/Logger.h>
#include <Poco/LoggingRegistry.h>

namespace poco_showcase::logging {

PriorityChannel::PriorityChannel() = default;

PriorityChannel::PriorityChannel(Poco::Message::Priority priority)
    : m_priority{priority} {}

PriorityChannel::PriorityChannel(Poco::AutoPtr<Channel> channel)
    : m_destination_channel{channel} {}

PriorityChannel::PriorityChannel(Poco::Message::Priority priority, Poco::AutoPtr<Channel> channel)
    : m_priority{priority}
    , m_destination_channel{channel} {}

void PriorityChannel::log(const Poco::Message &msg) {
    if (m_destination_channel and msg.getPriority() <= m_priority) {
        m_destination_channel->log(msg);
    }
}

void PriorityChannel::setProperty(const std::string &name, const std::string &value) {
    if (name.compare(0, 7, "channel") == 0) {
        m_destination_channel = Poco::LoggingRegistry::defaultRegistry().channelForName(value);
    } else if (name.compare(0, 5, "level") == 0) {
        m_priority = Poco::Logger::parseLevel(value);
    } else {
        Channel::setProperty(name, value);
    }
}

void PriorityChannel::set_channel(Poco::AutoPtr<Channel> channel) { m_destination_channel = channel; }

void PriorityChannel::set_level(Poco::Message::Priority priority) { m_priority = priority; }

PriorityChannel::~PriorityChannel() = default;

} // namespace poco_showcase::logging
