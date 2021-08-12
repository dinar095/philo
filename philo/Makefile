NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror
FUNCTIONS = srcs/breadcrumbs \
			srcs/carefree_life \
			srcs/care_free_f \
			srcs/supervisor \
			srcs/srcs \
			srcs/init \
			main
HEADER = headers/philo.h

OBJ = $(patsubst %,%.o,$(FUNCTIONS))
SRC = $(patsubst %,%.c,$(FUNCTIONS))

.PHONY: all clean fclean re

all: $(NAME)

obj_f: $(SRC) $(HEADER)
	$(CC) CFLAGS = -Wall -Wextra -Werror -c $(SRC)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(SRC) -pthread -o $(NAME)


clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

norm: $(SRC)
	norminette $(SRC)

.PHONY:		all clean fclean re norm
