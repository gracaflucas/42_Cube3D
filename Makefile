# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/07 12:15:28 by ana-lda-          #+#    #+#              #
#    Updated: 2025/04/07 13:13:45 by lufiguei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes -I./lib/libft -I./lib/get_next_line
SRCDIR = ./src
OBJDIR = ./obj
LIBFTDIR = ./lib/libft
LIBGNTLDIR = ./lib/get_next_line

SRCS = $(SRCDIR)/main.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
LIBFT = $(LIBFTDIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@printf "\r \e[1;32mcub3D\e[0m compiled successfully\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c ./includes/cub3D.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean
	@printf " \e[1;33mObjects Removed\n\e[0m"

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	@printf " \e[1;31mExecutable Deleted\n\e[0m"

re: fclean all
	@printf "\r \e[1;32mRefresh OK!\e[0m\n"

.PHONY: all clean fclean re