//
// Created by gennaro on 25/11/20.
//

#pragma once

#include <Poco/Util/Application.h>

namespace poco_showcase::util::application {

/// @brief A very basic application
/// The scope is to show which information are available when developing with Poco::Util library
class BasicApplication : public Poco::Util::Application {
public:
    BasicApplication();

    const char *name() const override;

protected:
    int main(const std::vector<std::string> &args) override;
};

} // namespace poco_showcase::util::application