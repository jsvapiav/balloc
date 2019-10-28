# set project name
project(utests)

# add utests source
set(SOURCE_EXE sanity_check.c)

# make executable
add_executable(sanity_check ${SOURCE_EXE})

# link balloc lib
target_link_libraries(sanity_check balloc)

# set compiler options
set(CXX_WAR_AS_ERR -Werror -Wall -pedantic)
set(CXX_MEM_DBG -fsanitize=address -fsanitize=leak -fsanitize=bounds)
target_compile_options(sanity_check PRIVATE ${CXX_WAR_AS_ERR})
# target_compile_options(sanity_check PRIVATE ${CXX_MEM_DBG})

# add tests
add_test(NAME utest_x86_64 COMMAND sanity_check)
