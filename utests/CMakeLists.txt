# set project name
project(utests)

# add pthread package
find_package (Threads)

# add utests source
set(SANITY_CHECK_EXE sanity_check.c)
set(MULTY_ALLOC_EXE multi_alloc.c)
set(THREADS_CHECK_EXE threads_check.c)

# make executable
add_executable(sanity_check ${SANITY_CHECK_EXE})
add_executable(multi_alloc ${MULTY_ALLOC_EXE})
add_executable(threads_check ${THREADS_CHECK_EXE})


# link balloc lib
target_link_libraries(sanity_check balloc)
target_link_libraries(multi_alloc balloc)
target_link_libraries(threads_check balloc ${CMAKE_THREAD_LIBS_INIT})

# set compiler options
set(CXX_WAR_AS_ERR -Werror -Wall -pedantic)
set(CXX_MEM_DBG -fsanitize=address -fsanitize=leak -fsanitize=bounds)
target_compile_options(sanity_check PRIVATE ${CXX_WAR_AS_ERR})
target_compile_options(multi_alloc PRIVATE ${CXX_WAR_AS_ERR})
target_compile_options(threads_check PRIVATE ${CXX_WAR_AS_ERR})
# target_compile_options(sanity_check PRIVATE ${CXX_MEM_DBG})

# add tests
add_test(NAME sanity_check COMMAND sanity_check)
add_test(NAME multi_alloc COMMAND multi_alloc)
add_test(NAME threads_check COMMAND threads_check)
