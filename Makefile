# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/07 12:15:28 by ana-lda-          #+#    #+#              #
#    Updated: 2025/04/13 17:03:30 by marvin           ###   ########.fr        #
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

SRCS = $(SRCDIR)/main.c\
	$(SRCDIR)/init.c\
	$(SRCDIR)/map_read.c\
	$(SRCDIR)/parsing.c\
	$(SRCDIR)/minimap_bonus.c\

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
MINILIBX = minilibx-linux/libmlx_Linux.a
MLX = -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm
LIBFT = $(LIBFTDIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFTDIR) -lft $(MLX) $(LDFLAGS) -o $(NAME)
	@printf "\r \e[1;32mcub3D\e[0m compiled successfully\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c ./includes/cub3D.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)
	
$(MINILIBX):
	$(MAKE) -C minilibx-linux

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C minilibx-linux clean
	@printf " \e[1;33mObjects Removed\n\e[0m"

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	$(MAKE) -C minilibx-linux clean
	@printf " \e[1;31mExecutable Deleted\n\e[0m"

re: fclean all
	@printf "\r \e[1;32mRefresh OK!\e[0m\n"

.PHONY: all clean fclean re
