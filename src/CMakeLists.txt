cmake_minimum_required(VERSION 3.20)
project(CmdProc)

#  Set C standard
set(CMAKE_C_STANDARD 99)

#  Include modules directory
include_directories(${CMAKE_SOURCE_DIR}/modules)


add_subdirectory(modules)
add_subdirectory(Unity)

#  Add library for cmdproc
#add_library(cmdproc modules/cmdproc.c)

#  Add library for unity
#add_library(unity Unity/src/unity.c)

#  Main executable
add_executable(main main.c)
target_link_libraries(main cmdproc)

#  Test executable
add_executable(tests tests.c)
target_link_libraries(tests cmdproc unity)

add_test(tests cmdproc)