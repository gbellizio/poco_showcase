//
// Created by gennaro on 25/11/20.
//

#include "util/application/with_options_application.h"
#include "logging/priority_channel.h"
#include "util/application_helpers/application_helpers.h"
#include "util/application_helpers/log_level_validator.h"
#include <Poco/LoggingFactory.h>
#include <Poco/String.h>
#include <Poco/Util/HelpFormatter.h>

#include <iostream>

namespace poco_showcase::util::application {

WithOptionsApplication::WithOptionsApplication() {
    poco_trace(logger(), __PRETTY_FUNCTION__);

    using poco_showcase::logging::PriorityChannel;

    // subsystems and other pluggable modules should be registered into the constructor
    Poco::LoggingFactory::defaultFactory().registerChannelClass("PriorityChannel",
                                                                new Poco::Instantiator<PriorityChannel, Poco::Channel>);
}

const char *WithOptionsApplication::name() const {
    poco_trace(logger(), __PRETTY_FUNCTION__);

    return "WithOptionsApplication";
}

void WithOptionsApplication::initialize(Poco::Util::Application &self) {
    poco_trace(logger(), __PRETTY_FUNCTION__);

    // loads configuration from default configuration file, if found
    loadConfiguration();

    if (m_help_requested) {
        return;
    }

    // triggers parent class initialization
    Application::initialize(self);

    // application initialization should happen here
}

void WithOptionsApplication::uninitialize() {
    poco_trace(logger(), __PRETTY_FUNCTION__);

    if (m_help_requested) {
        return;
    }

    // application specific uninitialization should happen here

    // finally, triggers parent class uninitialization
    Application::uninitialize();
}

void WithOptionsApplication::defineOptions(Poco::Util::OptionSet &options) {
    poco_trace(logger(), __PRETTY_FUNCTION__);

    Application::defineOptions(options);

    using Poco::Util::Option;
    using Poco::Util::OptionCallback;

    options.addOption( //
        Option("help", "h", "display help information on command line arguments")
            .required(false)
            .repeatable(false)
            .callback(OptionCallback<WithOptionsApplication>(this, &WithOptionsApplication::handle_help)));

    options.addOption( //
        Option("config-file", "c", "configuration file")
            .required(false)
            .repeatable(true)
            .callback(OptionCallback<WithOptionsApplication>(this, &WithOptionsApplication::handle_config))
            .argument("path"));

    options.addOption( //
        Option("log-level", "l", "root logger logging level")
            .required(false)
            .repeatable(false)
            .argument("level")
            .binding("logging.loggers.root.level")
            .validator(new application_helpers::LogLevelValidator));
}

void WithOptionsApplication::handleOption(const std::string &name, const std::string &value) {
    poco_trace(logger(), __PRETTY_FUNCTION__);

    Application::handleOption(name, value);
}

int WithOptionsApplication::main(const std::vector<std::string> &args) {
    poco_trace(logger(), __PRETTY_FUNCTION__);

    if (m_help_requested) {
        return Application::EXIT_OK;
    }

    application_helpers::dump_application_settings(*this);

    poco_fatal(logger(), "fatal message");
    poco_critical(logger(), "critical message");
    poco_error(logger(), "error message");
    poco_warning(logger(), "warning message");
    poco_notice(logger(), "notice message");
    poco_information(logger(), "information message");
    poco_debug(logger(), "debug message");
    poco_trace(logger(), "trace message");

    poco_information(Poco::Logger::get("MyClass"), "information message");

    Poco::ThreadPool::defaultPool().joinAll();

    return Application::EXIT_OK;
}

WithOptionsApplication::~WithOptionsApplication() { poco_trace(logger(), __PRETTY_FUNCTION__); }

void WithOptionsApplication::handle_config(const std::string &name, const std::string &value) {
    poco_trace(logger(), __PRETTY_FUNCTION__);

    loadConfiguration(value);
}

void WithOptionsApplication::handle_help(const std::string &name, const std::string &value) {
    poco_trace(logger(), __PRETTY_FUNCTION__);

    m_help_requested = true;
    stopOptionsProcessing();

    using Poco::Util::HelpFormatter;

    HelpFormatter helpFormatter(options());
    helpFormatter.setWidth(120);
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader("Sample application defining command line options");
    helpFormatter.format(std::cout);
}

} // namespace poco_showcase::util::application