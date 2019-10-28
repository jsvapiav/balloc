# set minimum cmake verision
cmake_minimum_required(VERSION 2.8)

# set project name
project(balloc)

# add balloc source
set(SOURCE_LIB balloc.c)

# make static lib
add_library(balloc STATIC ${SOURCE_LIB})

# set compiler options
set(CXX_WAR_AS_ERR -Werror -Wall -pedantic)
set(CXX_MEM_DBG -fsanitize=address -fsanitize=leak -fsanitize=bounds)
target_compile_options(balloc PRIVATE ${CXX_WAR_AS_ERR})
# target_compile_options(balloc PRIVATE ${CXX_MEM_DBG})
