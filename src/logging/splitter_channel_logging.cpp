//
// Created by gennaro on 27/11/20.
//

#include <Poco/ConsoleChannel.h>
#include <Poco/Logger.h>
#include <Poco/SimpleFileChannel.h>
#include <Poco/SplitterChannel.h>

int main(int argc, char **argv) {
    auto &logger          = Poco::Logger::root();
    auto splitter_channel = new Poco::SplitterChannel;
    splitter_channel->addChannel(new Poco::ConsoleChannel);
    splitter_channel->addChannel(new Poco::SimpleFileChannel("messages.log"));
    logger.setChannel(splitter_channel);
    logger.information("informative message from splitter channel");

    return 0;
}
