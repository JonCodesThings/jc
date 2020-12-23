cmake_minimum_required(VERSION 3.10)
project(glue C)

include_directories(.)
set(SOURCE_FILES glue.c glad.c)

add_library(glue STATIC ${SOURCE_FILES})

set(CMAKE_C_STANDARD 11)
