# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::   #
#    Makefile                                           :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+     #
#    By: cfrancie <cfrancie@student.42.fr>            +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2025/06/26 00:00:00 by cfrancie           #+#    #+#             #
#    Updated: 2025/06/26 00:00:00 by cfrancie          ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
LIBFTDIR = libft

# Source files
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

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(INCDIR) -I$(LIBFTDIR)/include

# Libraries
LIBFT = $(LIBFTDIR)/libft.a

# Rules
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
