cmake_minimum_required(VERSION 2.8) 

project(task_manager LANGUAGES C)

set(SOURCE_LIB task_manager.c)

add_library(task_manager STATIC ${SOURCE_LIB})