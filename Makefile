# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/07 12:15:28 by ana-lda-          #+#    #+#              #
#    Updated: 2025/04/26 16:51:05 by marvin           ###   ########.fr        #
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
SRC_DIR_BONUS = ./src_bonus/
SRC_DIR = ./src/
OBJ_DIR = ./objs/
OBJ_DIR_BONUS = ./objs_bonus/
SRCS = $(SRC_DIR)/main.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/map_read.c \
		$(SRC_DIR)parsing/parsing.c \
		$(SRC_DIR)parsing/texture.c \
		$(SRC_DIR)parsing/map_utils.c \
		$(SRC_DIR)free.c \
		$(SRC_DIR)/raycaster.c
SRC_BONUS = $(SRC_DIR_BONUS)/main_bonus.c \
		$(SRC_DIR_BONUS)/init_bonus.c \
		$(SRC_DIR_BONUS)parsing_bonus/parsing_bonus.c \
		$(SRC_DIR_BONUS)parsing_bonus/texture_bonus.c \
		$(SRC_DIR_BONUS)parsing_bonus/map_utils_bonus.c \
		$(SRC_DIR_BONUS)free_bonus.c \
		$(SRC_DIR_BONUS)minimap_bonus.c \
		$(SRC_DIR_BONUS)/raycaster_bonus.c
OBJ = $(SRCS:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
OBJ := $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(OBJ))
OBJ_BONUS := $(patsubst $(SRC_DIR_BONUS)%, $(OBJ_DIR_BONUS)%, $(OBJ_BONUS))
CC = cc
C_FLAGS = -Wall -Werror -Wextra -g -Iincludes -Ilib/libft
NAME = cub3D
NAME_BONUS = cub3D_bonus

all : $(NAME)
bonus : $(NAME_BONUS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) -c $< -o $@

$(OBJ_DIR_BONUS)%.o : $(SRC_DIR_BONUS)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) -c $< -o $@

$(NAME) : $(MLX) $(OBJ) $(LIBFT_LIB)
	@echo "$(CYAN)[!]$(RESET) Working on project ... "
	@$(CC) $(C_FLAGS) $(OBJ) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME) > /dev/null 2>&1
	@echo "$(GREEN)[✔] CUB3D compiled!$(RESET)"

$(NAME_BONUS) : $(MLX) $(OBJ_BONUS) $(LIBFT_LIB)
	@echo "$(CYAN)[!]$(RESET) Working on project ... "
	@$(CC) $(C_FLAGS) $(OBJ_BONUS) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME_BONUS) > /dev/null 2>&1
	@echo "$(GREEN)[✔] CUB3D_BONUS compiled!$(RESET)"

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
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR_BONUS)
	@make clean -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo "$(ORANGE)[✔] Objects Removed!$(RESET)"

fclean: clean
	@echo "$(CYAN)[!]$(RESET) Executing full cleaning..."
	@rm -rf $(NAME) $(NAME_BONUS)
	@rm -rf $(MLX_DIR)
	@make fclean -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo "$(RED)[✔] Full cleaning done!$(RESET)"

re: fclean all