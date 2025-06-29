NAME = ft_ls

SRCDIR = src
INCDIR = include
OBJDIR = obj
LIBFTDIR = libft

SRCFILES = main.c \
		   options.c \
		   ft_ls.c \
		   file_info.c \
		   sorting.c \
		   display.c \
		   utils.c \
		   error.c \

SRCS = $(addprefix $(SRCDIR)/, $(SRCFILES))
OBJS = $(addprefix $(OBJDIR)/, $(SRCFILES:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(INCDIR) -I$(LIBFTDIR)/include

LIBFT = $(LIBFTDIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFTDIR) -lft -o $(NAME)
	@echo "ft_ls compiled successfully!"

$(LIBFT):
	@make -C $(LIBFTDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@make -C $(LIBFTDIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
