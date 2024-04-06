cmake_minimum_required(VERSION 3.1)
project(main LANGUAGES C)


set(MY_HEADER_FILES
	# put all your .h here. Right now we have none.
	# Example : 
	# ../common/shader.hpp
)

set(MY_SOURCE_FILES
	# put all your .c/.cpp here.
	src/main.c
	# ../common/shader.cpp
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static")
endif()

# if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
# 	execute_process(COMMAND cd lib/Nuklear/src)
# 	execute_process(COMMAND sh ./paq.sh > ../nuklear.h)
# 	execute_process(COMMAND cd ../../..)
# elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
# 	message("You're on Windows !")
# endif()

include_directories(src/libs/dyn_array src/libs/utils src/libs/bst)

add_executable(${PROJECT_NAME}
	${MY_HEADER_FILES}
	${MY_SOURCE_FILES}
)

add_subdirectory(src/tasks)
add_subdirectory(src/libs/task_manager)
add_subdirectory(src/libs/dyn_array)
add_subdirectory(src/libs/bst)
add_subdirectory(src/libs/utils)

add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
add_subdirectory(lib/freetype EXCLUDE_FROM_ALL)
# add_subdirectory(lib/Nuklear EXCLUDE_FROM_ALL)


target_link_libraries(${PROJECT_NAME}
	PRIVATE glfw
	PRIVATE libglew_static
	PRIVATE glm
	PRIVATE freetype
	# PRIVATE nuklear
	PRIVATE task_manager
	PRIVATE dyn_array
	PRIVATE bst
	PRIVATE utils
	PRIVATE tasks
)

target_include_directories(${PROJECT_NAME}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src
	PRIVATE src/libs/task_manager
	PRIVATE src/libs/dyn_array
	PRIVATE src/libs/bst
	PRIVATE src/libs/utils
	PRIVATE src/tasks
)


# test if linux, mac or windows : 

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	message("You're on Mac OS !")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	message("You're on Linux !")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message("You're on Windows !")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # Yes this is weird but you have to repeat the "if" here.
