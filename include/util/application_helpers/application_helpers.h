//
// Created by gennaro on 25/11/20.
//

#pragma once

// fwd declarations
namespace Poco::Util {
class Application;
}

namespace poco_showcase::util::application_helpers {
void dump_application_settings(const Poco::Util::Application &app);
} // namespace poco_showcase::util::application_helpers
