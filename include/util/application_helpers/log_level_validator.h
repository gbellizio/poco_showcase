//
// Created by gennaro on 28/11/20.
//

#pragma once

#include <Poco/Util/Validator.h>

namespace poco_showcase::util::application_helpers {

class LogLevelValidator : public Poco::Util::Validator {
public:
    void validate(const Poco::Util::Option &option, const std::string &value) override;

protected:
    ~LogLevelValidator() override;
};

}