# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: desausag <desausag@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/04 12:21:58 by desausag          #+#    #+#              #
#    Updated: 2020/11/18 13:05:09 by desausag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
CC = gcc
FUNCTIONS = ft_isalnum ft_isalpha ft_isdigit ft_isascii \
				ft_isprint ft_strlen ft_strncmp ft_strrchr \
				ft_tolower ft_toupper ft_atoi ft_memset \
				ft_bzero ft_memcpy ft_memccpy ft_memmove \
				ft_memchr ft_memcmp ft_strchr ft_strlcat \
				ft_strlcpy ft_strnstr ft_strdup ft_calloc \
				ft_substr ft_strjoin ft_strtrim ft_itoa \
				ft_putchar_fd ft_putstr_fd ft_putendl_fd \
				ft_putnbr_fd ft_strmapi ft_split

BONUS = ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back \
		ft_lstdelone ft_lstclear ft_lstiter ft_lstmap

OBJ = $(patsubst %,%.o,$(FUNCTIONS))
SRC = $(patsubst %,%.c,$(FUNCTIONS))

BNS = $(patsubst %,%.o,$(BONUS))
BNS_SRC = $(patsubst %,%.c,$(BONUS))

.PHONY: all clean fclean re

all: $(NAME)

obj_f: $(SRC) libft.h
	gcc $(CFLAGS) -c $(SRC)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)


bonus: $(BNS) $(OBJ)
		ar rc $(NAME) $(OBJ) $(BNS)
		ranlib $(NAME);

clean:
	rm -rf $(OBJ) $(BNS)

fclean: clean
	rm -rf $(NAME)

re: fclean all