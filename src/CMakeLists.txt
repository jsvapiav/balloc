# set minimum cmake verision
cmake_minimum_required(VERSION 2.8)

# set project name
project(balloc)

# make platform specific decision
if (CMAKE_C_COMPILER_ID STREQUAL "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "gcc" OR CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set (COMP_PATH gcc)
    message(STATUS, "Compiler: ${CMAKE_C_COMPILER_ID}")
else ()
    message(FATAL_ERROR, "Unsupported compiler: ${CMAKE_C_COMPILER_ID}")
endif()

if (CMAKE_SYSTEM_PROCESSOR MATCHES "([xX]86$)")
    set (SYS_PATH x86)
    message(STATUS, "Processor type: ${CMAKE_SYSTEM_PROCESSOR}")
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "([xX]86_64)|(amd64)|(AMD64)")
    set (SYS_PATH x86_64)
    message(STATUS, "Processor type: ${CMAKE_SYSTEM_PROCESSOR}")
else ()
    message(FATAL_ERROR, "Unsupported processor type: ${CMAKE_SYSTEM_PROCESSOR}")
endif ()

set (PLATFORM_PATH platform/${COMP_PATH}/${SYS_PATH})
message(STATUS, "Include platform path: ${PLATFORM_PATH}")

# specify include dir
include_directories(${PLATFORM_PATH})

# add balloc source
set(SOURCE_LIB balloc.h balloc.c ${PLATFORM_PATH}/platform.h)

# make static lib
add_library(balloc STATIC ${SOURCE_LIB})

# set compiler options
set(CXX_WAR_AS_ERR -Werror -Wall -pedantic)
set(CXX_MEM_DBG -fsanitize=address -fsanitize=leak -fsanitize=bounds)
target_compile_options(balloc PRIVATE ${CXX_WAR_AS_ERR})
# target_compile_options(balloc PRIVATE ${CXX_MEM_DBG})



