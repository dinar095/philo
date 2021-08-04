cmake_minimum_required(VERSION 3.16)
project(philo C)
FILE(GLOB PHIL_SRC
		${CMAKE_CURRENT_SOURCE_DIR}/srcs/*.c)
set(CMAKE_C_STANDARD 99)

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libft)

add_executable(philo main.c headers/philo.h)

add_executable(sand
		sand.c
		${PHIL_SRC}
		)

add_executable(main
		main.c
		headers/philo.h
		${PHIL_SRC}
		)

target_link_libraries(
		sand
		libft
)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lpthread")