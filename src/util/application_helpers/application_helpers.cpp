//
// Created by gennaro on 25/11/20.
//

#include "util/application_helpers/application_helpers.h"
#include <Poco/DateTimeFormatter.h>
#include <Poco/String.h>
#include <Poco/Util/Application.h>
#include <Poco/Util/SystemConfiguration.h>

#include <algorithm>
#include <sstream>

// implementation details fwd declarations
namespace poco_showcase::util::application_helpers::detail {
void dump_application_properties(const Poco::Util::Application &app, std::ostream &os);
void dump_application_config(const Poco::Util::Application &app, std::ostream &os);
void dump_application_options(const Poco::Util::Application &app, std::ostream &os);
void visit_view(Poco::AutoPtr<Poco::Util::AbstractConfiguration> view, std::ostream &os, int level = 0);
} // namespace poco_showcase::util::application_helpers::detail

namespace poco_showcase::util::application_helpers {

void dump_application_settings(const Poco::Util::Application &app) {
    std::ostringstream os;
    detail::dump_application_properties(app, os);
    detail::dump_application_config(app, os);
    detail::dump_application_options(app, os);

    auto message = os.str();
    if (auto pos = message.find_last_of('\n'); pos != std::string::npos) {
        message.erase(pos);
    }
    poco_information(app.logger(), Poco::format("%s application settings:\n%s", std::string{app.name()}, message));
}

namespace detail {

void dump_application_properties(const Poco::Util::Application &app, std::ostream &os) {
    using namespace Poco;
    os << format("  properties\n"
                 "    name = %s\n"
                 "    startTime = %s\n"
                 "    commandPath = %s\n"
                 "    commandName = %s\n"
                 "    command line arguments = [%s]\n",
                 std::string{app.name()}, DateTimeFormatter::format(app.startTime(), "%Y-%m-%d %H:%M:%S%z"),
                 app.commandPath(), app.commandName(),
                 cat(std::string{", "}, std::begin(app.argv()), std::end(app.argv())));
}

inline void dump_application_config(const Poco::Util::Application &app, std::ostream &os) {
    using namespace Poco;

    using Keys    = Poco::Util::AbstractConfiguration::Keys;
    auto sections = Keys{};
    app.config().keys(sections);

    for (const auto &s : sections) {
        os << format("  %s configuration\n", s);
        visit_view(app.config().createView(s), os, 2);
    }
}

inline void dump_option(const Poco::Util::Option o, std::ostream &os) {
    os << Poco::format("      binding = %s\n"
                       "      shortName = %s\n"
                       "      fullName = %s\n"
                       "      description = %s\n"
                       "      argumentName = %s\n"
                       "      argumentRequired = %b\n"
                       "      required = %b\n"
                       "      repeatable = %b\n"
                       "      validator = %b\n",
                       o.binding(), o.shortName(), o.fullName(), o.description(), o.argumentName(),
                       o.argumentRequired(), o.required(), o.repeatable(), o.validator() != nullptr);
}

inline void dump_application_options(const Poco::Util::Application &app, std::ostream &os) {
    if (app.options().begin() == app.options().end()) {
        return;
    }

    using namespace Poco;

    os << "  options\n";
    for (const auto &o : app.options()) {
        os << format("    %s\n", o.fullName());
        dump_option(o, os);
    }
}

inline void visit_view(Poco::AutoPtr<Poco::Util::AbstractConfiguration> view, std::ostream &os, int level) {
    if (view) {
        using Keys = Poco::Util::AbstractConfiguration::Keys;
        auto keys  = Keys{};
        view->keys(keys);

        using namespace Poco;

        for (const auto &k : keys) {
            try {
                os << format("%s%s = %s\n", std::string(level * 2, ' '), k, view->getString(k));
            } catch (const Exception &ex) {
                auto sub_keys = Keys{};
                view->keys(k, sub_keys);
                auto sub_view = view->createView(k);

                os << format("%s%s\n", std::string(level * 2, ' '), k);
                visit_view(sub_view, os, level + 1);
            }
        }
    }
}

} // namespace detail
} // namespace poco_showcase::util::application_helpers
