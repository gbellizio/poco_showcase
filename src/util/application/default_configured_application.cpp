//
// Created by gennaro on 27/11/20.
//

#include "util/application/default_configured_application.h"
#include "util/application_helpers/application_helpers.h"

namespace poco_showcase::util::application {

const char *DefaultConfiguredApplication::name() const { return "DefaultConfiguredApplication"; }

int DefaultConfiguredApplication::main(const std::vector<std::string> &args) {
    application_helpers::dump_application_settings(*this);

    return Application::EXIT_OK;
}

void DefaultConfiguredApplication::initialize(Poco::Util::Application &self) {
    // the magic happens here
    loadConfiguration();

    // ... before triggering initialization in parent class
    Application::initialize(self);

    // application initialization should happen here
}

} // namespace poco_showcase::util::application