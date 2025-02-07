cmake_minimum_required(VERSION 3.10)
project(bang-lish)

set(CMAKE_C_STANDARD 17)

include_directories(includes)

file(GLOB SOURCES "src/*.c")

add_executable(banglish ${SOURCES})
