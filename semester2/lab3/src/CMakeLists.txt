cmake_minimum_required(VERSION 2.8)

project(main LANGUAGES C)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static")
endif()

include_directories(task_manager tasks)

add_executable(${PROJECT_NAME} main.c)

add_subdirectory(task_manager)
add_subdirectory(tasks)

target_link_libraries(${PROJECT_NAME} task_manager tasks)