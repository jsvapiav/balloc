# set minimum cmake verision
cmake_minimum_required(VERSION 2.8)

# set project name
project(balloc)

# add balloc source
set(SOURCE_LIB balloc.c)

# make static lib
add_library(balloc STATIC ${SOURCE_LIB})
