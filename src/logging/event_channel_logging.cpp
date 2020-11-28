//
// Created by gennaro on 27/11/20.
//

#include <Poco/EventChannel.h>
#include <Poco/FunctionDelegate.h>
#include <Poco/Logger.h>

#include <iostream>

int main(int argc, char **argv) {
    auto &logger       = Poco::Logger::root();
    auto event_channel = new Poco::EventChannel;
    logger.setChannel(event_channel);

    event_channel->messageLogged += Poco::FunctionDelegate<const Poco::Message, false>(
        [](const auto &msg) { std::cout << "got message: " << msg.getText() << '\n'; });

    logger.information("informative message");

    return 0;
}