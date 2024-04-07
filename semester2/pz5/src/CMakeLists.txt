cmake_minimum_required(VERSION 2.8)

project(main LANGUAGES C)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static")
endif()


include_directories(
    libs/task_manager
    libs/array_stack
    libs/list_stack
    libs/queue
    libs/utils
    tasks
)

add_executable(${PROJECT_NAME} main.c)

add_subdirectory(libs/task_manager)
add_subdirectory(libs/array_stack)
add_subdirectory(libs/list_stack)
add_subdirectory(libs/queue)
add_subdirectory(libs/utils)

add_subdirectory(tasks)

target_link_libraries(${PROJECT_NAME}
    PRIVATE task_manager
    PRIVATE tasks
    PRIVATE array_stack
    PRIVATE list_stack
    PRIVATE queue
    PRIVATE utils
)