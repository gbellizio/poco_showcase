//
// Created by gennaro on 27/11/20.
//

#include <Poco/Logger.h>
#include <Poco/SimpleFileChannel.h>

int main(int argc, char **argv) {
    using Poco::Logger;

    auto &logger = Logger::root();
    logger.setChannel(new Poco::SimpleFileChannel("messages.log"));

    logger.information("informative message");

    return 0;
}
