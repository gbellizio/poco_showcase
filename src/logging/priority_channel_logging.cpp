//
// Created by gennaro on 27/11/20.
//

#include "logging/priority_channel.h"
#include <Poco/ConsoleChannel.h>
#include <Poco/Logger.h>
#include <Poco/SimpleFileChannel.h>
#include <Poco/SplitterChannel.h>

int main(int argc, char **argv) {
    auto &logger          = Poco::Logger::root();
    auto splitter_channel = new Poco::SplitterChannel;
    auto priority_channel = new poco_showcase::logging::PriorityChannel(Poco::Message::PRIO_ERROR,
                                                                        new Poco::SimpleFileChannel("messages.log"));

    splitter_channel->addChannel(new Poco::ConsoleChannel);
    splitter_channel->addChannel(priority_channel);
    logger.setChannel(splitter_channel);
    logger.information("informative message from splitter (filtered) channel");
    logger.warning("warning message from splitter (filtered) channel");
    logger.error("error message from splitter (filtered) channel");

    return 0;
}
