# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/07 12:15:28 by ana-lda-          #+#    #+#              #
#    Updated: 2025/04/18 15:25:55 by ana-lda-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = cub3D
CC       = cc
CFLAGS   = -Wall -Wextra -Werror -g
LDFLAGS  =

# ========== Directories ==========
SRCDIR     = src
OBJDIR     = obj
INCLUDES   = -Iincludes -Ilib/libft -Ilib/get_next_line
LIBFTDIR   = lib/libft
GNTLDIR    = lib/get_next_line
MLXDIR     = includes/minilibx-linux

# ========== Libraries ==========
LIBFT      = $(LIBFTDIR)/libft.a
MLX_LIB    = $(MLXDIR)/libmlx.a
MLX_FLAGS  = -L$(MLXDIR) -lmlx -lX11 -lXext -lm

# ========== Source Files ==========
SRCS = $(SRCDIR)/main.c \
       $(SRCDIR)/init.c \
       $(SRCDIR)/map_read.c \
       $(SRCDIR)/parsing.c \
       $(SRCDIR)/minimap_bonus.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# ========== Build Targets ==========
all: $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFTDIR) -lft $(MLX_FLAGS) $(LDFLAGS) -o $(NAME)
	@printf "\e[1;32m✔ cub3D compiled successfully!\e[0m\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c includes/cub3D.h
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

$(MLX_LIB):
	@if [ ! -d "$(MLXDIR)" ]; then \
		echo "\e[1;36m[!] Cloning MiniLibX into includes...\e[0m"; \
		cd includes && git clone https://github.com/42Paris/minilibx-linux.git > /dev/null 2>&1; \
	fi
	@rm -rf $(MLXDIR)/.git
	@$(MAKE) -C $(MLXDIR)

# ========== Cleaning ==========
clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFTDIR) clean
	@$(MAKE) -C $(MLXDIR) clean
	@printf "\e[1;33m* Object files removed.\e[0m\n"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean
	@rm -rf $(MLXDIR)
	@printf "\e[1;31m* Executable and MiniLibX removed.\e[0m\n"

re: fclean all
	@printf "\e[1;32m* Project rebuilt successfully.\e[0m\n"

.PHONY: all clean fclean re
