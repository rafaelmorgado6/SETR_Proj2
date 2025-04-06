cmake_minimum_required(VERSION 3.20)
project(CmdProc)

#  Set C standard
set(CMAKE_C_STANDARD 99)

#  Include modules directory
include_directories(${CMAKE_SOURCE_DIR}/src/modules)

#  Add library for cmdproc
add_library(cmdproc modules/cmdproc.c)

#  Add library for cmdproc
add_library(unity Unity/src/unity.c)

#  Main executable
add_executable(main main.c)
target_link_libraries(main cmdproc)

#  Test executable
add_executable(tests tests.c)
target_link_libraries(tests cmdproc unity)
