NAME = ft_ls
LIBFT = ./libft/libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft/includes
SRC = ft_ls.c src/parsing.c src/file_info.c src/options.c \
      src/display.c src/recursion.c src/utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all
