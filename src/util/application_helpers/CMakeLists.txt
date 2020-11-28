add_library(helpers STATIC)

target_sources(helpers
        PRIVATE
        application_helpers.cpp
        log_level_validator.cpp)

target_link_libraries(helpers
        PUBLIC
        logging
        Poco::Util)
