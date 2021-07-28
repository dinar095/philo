cmake_minimum_required(VERSION 3.19)
project(philo C)
FILE(GLOB PHIL_SRC
		${CMAKE_CURRENT_SOURCE_DIR}/libft/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/libft/*.c)
set(CMAKE_C_STANDARD 99)

add_executable(philo main.c headers/philo.h)