NAME = philo

CC = gcc
FUNCTIONS = srcs/ft_atoi \
			srcs/ft_isdigit \
			srcs/ft_putnbr_fd	\
			srcs/ft_putstr_fd	\
			main
HEADER = headers/philo.h



OBJ = $(patsubst %,%.o,$(FUNCTIONS))
SRC = $(patsubst %,%.c,$(FUNCTIONS))

.PHONY: all clean fclean re

all: $(NAME)

obj_f: $(SRC) $(HEADER)
	$(CC) -c $(SRC)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(SRC) -pthread -o $(NAME)


clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:		all clean fclean re
