# set project name
project(utests)

# add utests source
set(SOURCE_EXE utest.c)

# make executable
add_executable(utest ${SOURCE_EXE})

# link balloc lib
target_link_libraries(main {CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libballoc.a)
