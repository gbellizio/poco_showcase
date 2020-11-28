//
// Created by gennaro on 27/11/20.
//

#include <Poco/ConsoleChannel.h>
#include <Poco/Logger.h>

int main(int argc, char **argv) {
    using Poco::ConsoleChannel, Poco::Logger, Poco::Message;

    auto &logger = Logger::root();         // gets the root logger
    logger.setChannel(new ConsoleChannel); // attach a channel
    logger.setLevel(Message::PRIO_ERROR);  // sets the log level

    logger.debug("value of a is 2");
    logger.fatal("cannot allocate memory");

    return 0;
}