# set project name
project(utests)

# add utests source
set(SOURCE_EXE utest.c)

# make executable
add_executable(utest ${SOURCE_EXE})

# link balloc lib
target_link_libraries(utest balloc)

# set compiler options
set(ALL_WAR_AS_ERR -Werror -Wall -pedantic)
target_compile_options(utest PRIVATE ${ALL_WAR_AS_ERR})

# add tests
add_test(NAME utest_x86_64 COMMAND utest)
