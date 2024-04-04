cmake_minimum_required(VERSION 2.8) 

project(bst LANGUAGES C)

set(SOURCE_LIB
    bst.c
    bst_utils.c
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB})