# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/07 12:15:28 by ana-lda-          #+#    #+#              #
#    Updated: 2025/06/12 10:56:28 by lufiguei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLUE = \e[1;034m
RED = \e[0;31m
MAGENTA = \033[1;35m
ORANGE = \033[1;38;5;208m
GREY = \033[0;37m
CYAN = \e[1;36m
RESET = \e[0m
GREEN = \e[0;32m

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
		$(SRC_DIR)/moves.c \
		$(SRC_DIR)/raycaster_utils.c \
		$(SRC_DIR)parsing/parsing.c \
		$(SRC_DIR)parsing/parsing_utils.c \
		$(SRC_DIR)parsing/parsing_utils2.c \
		$(SRC_DIR)parsing/texture.c \
		$(SRC_DIR)parsing/texture_utils.c \
		$(SRC_DIR)parsing/map_utils.c \
		$(SRC_DIR)free.c \
		$(SRC_DIR)/raycaster.c

SRC_BONUS = $(SRC_DIR_BONUS)/main_bonus.c \
		$(SRC_DIR_BONUS)/init_bonus.c \
		$(SRC_DIR_BONUS)parsing_bonus/parsing_bonus.c \
		$(SRC_DIR_BONUS)parsing_bonus/texture_bonus.c \
		$(SRC_DIR_BONUS)parsing_bonus/map_utils_bonus.c \
		$(SRC_DIR_BONUS)parsing_bonus/parsing_utils_bonus.c \
		$(SRC_DIR_BONUS)parsing_bonus/texture_utils_bonus.c \
		$(SRC_DIR_BONUS)free_bonus.c \
		$(SRC_DIR_BONUS)minimap_bonus.c \
		$(SRC_DIR_BONUS)raycaster_utils_bonus.c \
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
	@echo "$(CYAN)[!]$(RESET) Compiling project ..."
	@$(CC) $(C_FLAGS) $(OBJ) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME) > /dev/null
	@echo "$(GREEN)[✔] CUB3D compiled!$(RESET)"

$(NAME_BONUS) : $(MLX) $(OBJ_BONUS) $(LIBFT_LIB)
	@echo "$(CYAN)[!]$(RESET) Compiling bonus ..."
	@$(CC) $(C_FLAGS) $(OBJ_BONUS) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME_BONUS) > /dev/null
	@echo "$(GREEN)[✔] CUB3D_BONUS compiled!$(RESET)"

$(LIBFT_LIB):
	@echo "$(CYAN)[!]$(RESET) Compiling Libft ..."
	@make -C $(LIBFT_DIR) > /dev/null
	@echo "$(GREEN)[✔] LIBFT compiled!$(RESET)"

$(MLX): $(MLX_DIR)
	@rm -rf include/minilibx-linux/.git
	@make -C $(MLX_DIR) >/dev/null 2>&1
$(MLX_DIR):
	@echo "$(CYAN)[!]$(RESET) Cloning MiniLibX ..."
	@git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR) > /dev/null 2>&1


	@echo "$(CYAN)[!]$(RESET) Building MiniLibX ..."
	@make -C $(MLX_DIR) > /dev/null 2>&1
	@echo "$(GREEN)[✔] MiniLibX built!$(RESET)"

clean:
	@echo "$(CYAN)[!]$(RESET) Cleaning Objects ..."
	@rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)
	@make clean -C $(LIBFT_DIR) > /dev/null
	@echo "$(ORANGE)[✔] Objects Removed!$(RESET)"

fclean: clean
	@echo "$(CYAN)[!]$(RESET) Full clean in progress..."
	@rm -rf $(NAME) $(NAME_BONUS)
	@rm -rf $(MLX_DIR)
	@make fclean -C $(LIBFT_DIR) > /dev/null
	@echo "$(RED)[✔] All cleaned!$(RESET)"

re: fclean all
