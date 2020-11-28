//
// Created by gennaro on 27/11/20.
//

#include <Poco/Logger.h>
#include <Poco/SyslogChannel.h>

int main(int argc, char **argv) {
    auto &logger = Poco::Logger::root();
    logger.setChannel(new Poco::SyslogChannel);

    logger.error("error message from a user application");

    return 0;
}
