cmake_minimum_required(VERSION 2.8) 

project(tasks)

file(GLOB SOURCE_FILES *.c)


add_library(tasks STATIC ${SOURCE_FILES})
target_link_libraries(tasks
    PRIVATE glfw
    PRIVATE libglew_static
    PRIVATE glm
    PRIVATE freetype
    PRIVATE dyn_array
    PRIVATE bst
    PRIVATE utils
)