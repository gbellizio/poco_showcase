cmake_minimum_required(VERSION 3.17)
project(PocoShowcase)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Poco REQUIRED COMPONENTS Foundation Util)

include_directories(include)

add_subdirectory(src/logging)
add_subdirectory(src/util)
add_subdirectory(presentation)