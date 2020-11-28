add_executable(simplest_application)

target_sources(simplest_application
        PRIVATE
        simplest_application.cpp)

target_link_libraries(simplest_application
        PRIVATE
        Poco::Util)

application_example(BasicApplication)
application_example(DefaultConfiguredApplication)
application_example(WithOptionsApplication)
application_example(ModularApplication)