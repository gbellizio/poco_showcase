add_library(logging STATIC)

target_sources(logging
        PRIVATE
        priority_channel.cpp)

target_link_libraries(logging
        PUBLIC
        Poco::Foundation)

function(logging_example)
    add_executable(${ARGV0})

    target_sources(${ARGV0}
            PRIVATE
            ${ARGV0}.cpp)

    target_link_libraries(${ARGV0}
            PRIVATE
            logging)
endfunction()

logging_example(console_logging)
logging_example(simple_file_logging)
logging_example(splitter_channel_logging)
logging_example(async_channel_logging)
logging_example(syslog_logging)
logging_example(event_channel_logging)
logging_example(formatting_channel_logging)
logging_example(priority_channel_logging)