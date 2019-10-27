# set minimum cmake verision
cmake_minimum_required(VERSION 2.8)

# set project name
project(balloc)

# add balloc lib
set(SOURCE_LIB src/balloc.c)

# add static lib
add_library(balloc STATIC ${SOURCE_LIB})
