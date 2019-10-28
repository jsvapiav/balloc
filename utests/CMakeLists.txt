# set project name
project(utests)

# add utests source
set(SOURCE_EXE utest.c)

# make executable
add_executable(utest ${SOURCE_EXE})

# link balloc lib
target_link_libraries(utest balloc)

# set compiler options
set(CXX_WAR_AS_ERR -Werror -Wall -pedantic)
set(CXX_MEM_DBG -fsanitize=address -fsanitize=leak -fsanitize=bounds)
target_compile_options(utest PRIVATE ${CXX_WAR_AS_ERR})
# target_compile_options(utest PRIVATE ${CXX_MEM_DBG})

# add tests
add_test(NAME utest_x86_64 COMMAND utest)
