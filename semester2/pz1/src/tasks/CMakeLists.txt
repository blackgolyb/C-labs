cmake_minimum_required(VERSION 2.8) 

project(tasks)

file(GLOB SOURCE_FILES *.c)
# include_directories(../libs/hash_table)

add_library(tasks STATIC ${SOURCE_FILES})
target_link_libraries(tasks PRIVATE table task_manager linked_list utils)