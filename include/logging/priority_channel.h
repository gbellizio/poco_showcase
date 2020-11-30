//
// Created by gennaro on 25/11/20.
//

#pragma once

#include <Poco/Channel.h>
#include <Poco/Message.h>

namespace poco_showcase::logging {

/// @brief A Poco::Channel that filters messages based on their priority
class PriorityChannel : public Poco::Channel {
public:
    PriorityChannel(); // needed by Poco::AbstractInstantiator
    explicit PriorityChannel(Poco::Message::Priority priority);
    explicit PriorityChannel(Poco::AutoPtr<Channel> channel);
    PriorityChannel(Poco::Message::Priority priority, Poco::AutoPtr<Channel> channel);

    /// @brief Logs a message
    /// This method is called by the framework when a message has to be logged.
    /// Represents the customization point for the logging channel chain. Here, we stop
    /// to propagate the message if its priority is lower than the channel priority.
    /// @param msg the message to log
    void log(const Poco::Message &msg) override;

    /// @brief Sets or changes a configuration property
    /// The supported properties are "channel" and "level". The former must be a valid channel name, the latter must
    /// a valid Poco::Message::Priority value ("trace", "debug", etc.)
    /// This method is usually called by the framework when dealing with configuration files.
    /// @param name property name
    /// @param value property value
    void setProperty(const std::string &name, const std::string &value) override;

    /// @brief Sets the destination channel
    /// @param channel
    void set_channel(Poco::AutoPtr<Channel> channel);

    /// @brief Sets the log level (or priority threshold)
    /// @param priority
    void set_level(Poco::Message::Priority priority);

protected:
    ~PriorityChannel() override;

private:
    Poco::AutoPtr<Channel> m_destination_channel;
    int m_priority = {Poco::Message::PRIO_INFORMATION};
};

} // namespace poco_showcase::logging
