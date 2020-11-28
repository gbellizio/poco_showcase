//
// Created by gennaro on 25/11/20.
//

#pragma once

#include <Poco/Util/Application.h>

namespace poco_showcase::util::application {

/// @brief A more complete application showing how to deal with command line arguments and other useful stuff.
class WithOptionsApplication : public Poco::Util::Application {
public:
    WithOptionsApplication();

    const char *name() const override;

protected:
    void initialize(Application &self) override;
    void uninitialize() override;
    void defineOptions(Poco::Util::OptionSet &options) override;
    void handleOption(const std::string &name, const std::string &value) override;
    int main(const std::vector<std::string> &args) override;
    ~WithOptionsApplication() override;

private:
    bool m_help_requested = {};

    void handle_config(const std::string &name, const std::string &value);
    void handle_help(const std::string &name, const std::string &value);
};

} // namespace poco_showcase::util::application