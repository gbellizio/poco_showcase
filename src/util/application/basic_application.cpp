//
// Created by gennaro on 25/11/20.
//

#include "util/application/basic_application.h"
#include "util/application_helpers/application_helpers.h"

namespace poco_showcase::util::application {

BasicApplication::BasicApplication() = default;

int BasicApplication::main(const std::vector<std::string> &args) {
    application_helpers::dump_application_settings(*this);

    return Application::EXIT_OK;
}

const char *BasicApplication::name() const { return "BasicApplication"; }

} // namespace poco_showcase::util::application