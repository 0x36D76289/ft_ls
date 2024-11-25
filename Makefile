NAME = ft_ls
LIBFT = ./libft/libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft/includes
SRC = ft_ls.c src/parsing.c src/file_info.c src/options.c \
      src/display.c src/recursion.c src/utils.c
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

all: $(NAME)

$(LIBFT):
	make -C libft

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re