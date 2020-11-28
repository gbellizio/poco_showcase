//
// Created by gennaro on 27/11/20.
//

#include <Poco/ConsoleChannel.h>
#include <Poco/FormattingChannel.h>
#include <Poco/Logger.h>
#include <Poco/PatternFormatter.h>

int main(int argc, char **argv) {
    auto &logger            = Poco::Logger::get("SampleApp");
    auto pattern            = new Poco::PatternFormatter("%L%Y-%m-%d %H:%M:%S.%F -%q- [%s] %t");
    auto formatting_channel = new Poco::FormattingChannel(pattern);
    formatting_channel->setChannel(new Poco::ConsoleChannel);
    logger.setChannel(formatting_channel);
    logger.information("a formatted informative message");

    return 0;
}