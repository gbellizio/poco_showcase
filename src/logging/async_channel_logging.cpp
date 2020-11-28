//
// Created by gennaro on 27/11/20.
//

#include <Poco/AsyncChannel.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/Logger.h>
#include <Poco/ThreadPool.h>

int main(int argc, char **argv) {
    auto &logger = Poco::Logger::root();
    logger.setChannel(new Poco::AsyncChannel(new Poco::ConsoleChannel));

    logger.information("informative async message");

    Poco::ThreadPool::defaultPool().joinAll(); // UB is guaranteed if removed!

    return 0;
}
