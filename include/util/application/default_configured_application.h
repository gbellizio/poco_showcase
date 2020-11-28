//
// Created by gennaro on 27/11/20.
//

#pragma once

#include <Poco/Util/Application.h>

namespace poco_showcase::util::application {

/// @brief Shows automatic configuration file handling
class DefaultConfiguredApplication : public Poco::Util::Application {
public:
    const char *name() const override;

protected:
    void initialize(Application &self) override;

    int main(const std::vector<std::string> &args) override;
};

} // namespace poco_showcase::util::application