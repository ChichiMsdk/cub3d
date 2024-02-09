SRC = main.c hook_utils.c draw.c line.c control.c
NAME = cub3d
CC = cc
OBJ = ${SRC:.c=.o}
FLAGS = -Wall -Wextra -Werror
DEBUG = -g
FSAN = -fsanitize=address
LIB = -L include/libft -lft -lmlx -lXext -lX11
INCL = -I include/
OS = -D$(shell uname)

all: lib $(NAME)

val: lib
	$(CC) $(DEBUG) $(SRC) $(LIB) -o $(NAME)

lib:
	make -C include/libft

$(NAME): objs
	$(CC) $(OS) $(FSAN) $(INCL) $(DEBUG) $(SRC) $(LIB) -o $(NAME)

objs:
	$(CC) $(OS) $(FSAN) $(INCL) $(DEBUG) -c $(SRC)

clean:
	rm -f $(OBJ)
	make -C include/libft/ clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(NAME).dSYM
	make -C include/libft/ fclean

fc: fclean

bear:
	@bear -- make re

re: clean all
