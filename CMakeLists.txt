cmake_minimum_required(VERSION 3.22)
project(Lab4_2)

set(CMAKE_CXX_STANDARD 17)

#find_library(LIB_TO_INCLUDE classes /home/kristofer/2_sem_prog/Lab3_2/Lib)
#find_path (LIB_INCLUDES lib_classes.h definitions.h /home/kristofer/2_sem_prog/Lab3_2/Lib/headers)
#include_directories(${LIB_INCLUDES})

add_executable(Lab4_2 Lab4_2.cpp draw_func.h draw_func.cpp print_func.h print_func.cpp table_func.h table_func.cpp lib_strings.h lib_strings.cpp lib_classes.h lib_classes.cpp)

#target_link_libraries(Lab3_2 ${LIB_TO_INCLUDE})
