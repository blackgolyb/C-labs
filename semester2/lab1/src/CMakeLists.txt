cmake_minimum_required(VERSION 2.8)

project(main LANGUAGES C)

include_directories(task_manager tasks libs/hash_table libs/table)

add_executable(${PROJECT_NAME} main.c)

add_subdirectory(task_manager)
add_subdirectory(tasks)
add_subdirectory(libs)

target_link_libraries(${PROJECT_NAME} task_manager tasks hash_table table)