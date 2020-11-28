//
// Created by gennaro on 28/11/20.
//

#include "util/application_helpers/log_level_validator.h"
#include <Poco/Format.h>
#include <Poco/String.h>
#include <Poco/Util/OptionException.h>

#include <set>

namespace poco_showcase::util::application_helpers {

namespace {
struct icompare {
    bool operator()(const std::string &lhs, const std::string &rhs) const noexcept {
        return Poco::icompare(lhs, rhs) < 0;
    }
};

inline const std::set<std::string, icompare> m_levels{"fatal",  "critical",    "error", "warning",
                                                      "notice", "information", "debug", "trace"};
} // namespace

void LogLevelValidator::validate(const Poco::Util::Option &option, const std::string &value) {
    if (auto it = m_levels.find(value); it == std::end(m_levels)) {
        throw Poco::Util::OptionException(Poco::format(R"(invalid log level value "%s")", value));
    }
}

LogLevelValidator::~LogLevelValidator() = default;

} // namespace poco_showcase::util::application_helpers
