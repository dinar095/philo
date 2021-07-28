cmake_minimum_required(VERSION 3.17)
project(Libft C)

set(CMAKE_C_STANDARD 11)


include_directories(.)

add_executable(Libft
        ft_isalpha.c
        ft_isdigit.c
        ft_strlen.c
        ft_toupper.c ft_strrchr.c ft_strncmp.c libft.h ft_isalnum.c ft_isascii.c ft_isprint.c ft_tolower.c ft_atoi.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strnstr.c ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c ft_split.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c)

add_executable(ft_toupper ft_toupper.c)
add_executable(ft_strlen ft_strlen.c)
add_executable(ft_isdigit ft_isdigit.c)
add_executable(ft_isalpha ft_isalpha.c)
add_executable(ft_strrchr ft_strrchr.c)
add_executable(ft_strncmp ft_strncmp.c)
add_executable(ft_isalnum ft_isalnum.c)
add_executable(ft_isascii ft_isascii.c)
add_executable(ft_isprint ft_isprint.c)
add_executable(ft_atoi ft_atoi.c)
add_executable(ft_memset ft_memset.c)
add_executable(ft_bzero ft_bzero.c)
add_executable(ft_memcpy ft_memcpy.c)
add_executable(ft_memccpy ft_memccpy.c)
add_executable(ft_memcmp ft_memcmp.c)
add_executable(ft_strnstr ft_strnstr.c)
add_executable(ft_strtrim ft_strtrim.c ft_strlen ft_strlen.c ft_strchr ft_strchr.c ft_substr ft_substr.c ft_strlcpy ft_strlcpy.c)
add_executable(ft_itoa ft_itoa.c)
add_executable(ft_putnbr_fd ft_putnbr_fd.c)
add_executable(ft_split ft_split.c)