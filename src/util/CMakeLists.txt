#[[
Converts a string from PascalCase to snake_case
credit: https://github.com/ros2/rosidl/blob/master/rosidl_cmake/cmake/string_camel_case_to_lower_case_underscore.cmake
]]#
function(pascal_to_snake_case str var)
    # insert an underscore before any upper case letter
    # which is not followed by another upper case letter
    string(REGEX REPLACE "(.)([A-Z][a-z]+)" "\\1_\\2" value "${str}")
    # insert an underscore before any upper case letter
    # which is preceded by a lower case letter or number
    string(REGEX REPLACE "([a-z0-9])([A-Z])" "\\1_\\2" value "${value}")
    string(TOLOWER "${value}" value)
    set(${var} "${value}" PARENT_SCOPE)
endfunction()

#[[
Generate targets for compiling Poco::Util::Application derived applications.
The function assumes that the class is declared into a header file whose name is
obtained by converting the class name into snake case. The implementation file is
assumed to follow the same pattern.

namespace: is the namespace in which the class was declared
class: is the class name
]]#
function(util_application namespace class)
    pascal_to_snake_case(${class} TARGET)

    add_executable(${TARGET})

    target_sources(${TARGET}
            PRIVATE
            main.cpp
            ${TARGET}.cpp)

    target_compile_definitions(${TARGET}
            PRIVATE
            APP_HEADER_FILE="util/application/${TARGET}.h"
            APP_CLASS=${namespace}::${class}
            )

    target_link_libraries(${TARGET}
            PRIVATE
            logging
            helpers
            Poco::Util)
endfunction()

#[[
Defines Poco::Util::Application example targets
class is the class name implementing the application
#]]
function(application_example class)
    util_application(poco_showcase::util::application ${class})
endfunction()

add_subdirectory(application_helpers)
add_subdirectory(application)
