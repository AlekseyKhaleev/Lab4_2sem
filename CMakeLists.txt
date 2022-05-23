cmake_minimum_required(VERSION 3.22)
project(Lab4_2)

set(CMAKE_CXX_STANDARD 17)

find_library(LIB_TO_INCLUDE library /home/kristofer/2_sem_prog/Lab4_2/Lib)
find_path (LIB_INCLUDES definitions.h lib_classes.h lib_strings.h lib_draw.h lib_print.h lib_table.h /home/kristofer/2_sem_prog/Lab4_2/Lib/headers)
include_directories(${LIB_INCLUDES})

add_executable(Lab4_2 Lab4_2.cpp lib_strings.cpp lib_classes.cpp)

target_link_libraries(Lab4_2 ${LIB_TO_INCLUDE})
