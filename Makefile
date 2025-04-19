# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/07 12:15:28 by ana-lda-          #+#    #+#              #
#    Updated: 2025/04/18 20:35:23 by ana-lda-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \e[0;32m
BLUE = \e[1;034m
RED = \e[0;31m
MAGENTA = \033[1;35m
ORANGE = \033[1;38;5;208m
GREY = \033[0;37m
CYAN = \e[1;36m
RESET = \e[0m

LIBFT_LIB = lib/libft/libft.a
LIBFT_DIR = lib/libft
MLX_FLAGS = -Lincludes/minilibx-linux -lmlx -L/usr/lib -Iincludes/minilibx-linux -lXext -lX11 -lm -lz
MLX_DIR = includes/minilibx-linux/
MLX = $(MLX_DIR)libmlx.a
SRC_DIR = ./src/
OBJ_DIR = ./objs/
SRCS = $(SRC_DIR)/main.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/map_read.c \
		$(SRC_DIR)parsing/parsing.c \
		$(SRC_DIR)parsing/texture.c \
		$(SRC_DIR)parsing/map_utils.c \
		$(SRC_DIR)free.c \
		$(SRC_DIR)/minimap_bonus.c
OBJ = $(SRCS:.c=.o)
OBJ := $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(OBJ))
CC = cc
C_FLAGS = -Wall -Werror -Wextra -g -Iincludes -Ilib/libft
NAME = cub3D
NAME_BONUS = cub3D_bonus

all : $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) -c $< -o $@

$(NAME) : $(MLX) $(OBJ) $(LIBFT_LIB)
	@echo "$(CYAN)[!]$(RESET) Working on project ... "
	@$(CC) $(C_FLAGS) $(OBJ) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME) > /dev/null 2>&1
	@echo "$(GREEN)[✔] CUB3D compiled!$(RESET)"

$(LIBFT_LIB) : $(LIBFT_DIR)
	@make -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo "$(GREEN)[✔] LIBFT compiled!$(RESET)"

$(MLX): $(MLX_DIR)
	@rm -rf includes/minilibx-linux/.git
	@make -C $(MLX_DIR) >/dev/null 2>&1

$(MLX_DIR):
	@echo "$(CYAN)[!]$(RESET) Preparing minilibx ..."
	@cd includes && git clone https://github.com/42Paris/minilibx-linux.git > /dev/null 2>&1

clean:
	@echo "$(CYAN)[!]$(RESET) Cleaning Objects ..."
	@make clean -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo "$(ORANGE)[✔] Objects Removed!$(RESET) "

fclean: clean
	@echo "$(CYAN)[!]$(RESET) Executing full cleaning..."
	@make fclean -C $(LIBFT_DIR) > /dev/null 2>&1
	@rm -rf $(NAME) $(MLX_DIR)
	@echo "$(RED)[✔] Full cleaning done!$(RESET) "

re: fclean all