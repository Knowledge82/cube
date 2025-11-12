# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 16:54:19 by vdarsuye          #+#    #+#              #
#    Updated: 2025/11/12 14:46:32 by vdarsuye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
RESET = \033[0m
RED = \033[31m
GREEN = \033[32m
NEON_GREEN = \033[92m
MATRIX_GREEN = \033[38;2;10;255;10m
YELLOW = \033[33m
BLUE = \033[34m

# Vars
NAME = cub3D
NAME_BONUS = cub3D_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

# Dirs
SRCS_DIR = src
SRCS_DIR_BONUS = src/bonus
OBJS_DIR = obj
OBJS_DIR_BONUS = obj/bonus
LIBFT_DIR = ./libft
MLX_DIR = ./MLX42
MLX_BUILD = $(MLX_DIR)/build

# Libs
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_BUILD)/libmlx42.a

# Headers
INCLUDES = -I$(SRCS_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)/include/MLX42

# Linker flags
MLX_LDFLAGS = $(MLX_LIB) -lglfw -lm -ldl -pthread

# Src files
SRCS = $(SRCS_DIR)/bfs.c \
	$(SRCS_DIR)/draw.c \
	$(SRCS_DIR)/draw_utils.c \
	$(SRCS_DIR)/file.c \
	$(SRCS_DIR)/free.c \
	$(SRCS_DIR)/init.c \
	$(SRCS_DIR)/main.c \
	$(SRCS_DIR)/map.c \
	$(SRCS_DIR)/map_utils.c \
	$(SRCS_DIR)/movement.c \
	$(SRCS_DIR)/parse_color.c \
	$(SRCS_DIR)/parse_config.c \
	$(SRCS_DIR)/parse_map.c \
	$(SRCS_DIR)/parse_texture.c \
	$(SRCS_DIR)/parse_utils.c \
	$(SRCS_DIR)/player.c \
	$(SRCS_DIR)/queue.c \
	$(SRCS_DIR)/ray.c \
	$(SRCS_DIR)/ray_utils.c \
	$(SRCS_DIR)/render.c \
	$(SRCS_DIR)/rotation.c \
	$(SRCS_DIR)/textures.c \
	$(SRCS_DIR)/utils.c \
	$(SRCS_DIR)/validation.c \



SRCS_BONUS = $(SRCS_DIR_BONUS)/bfs.c \
	$(SRCS_DIR_BONUS)/draw.c \
	$(SRCS_DIR_BONUS)/draw_utils.c \
	$(SRCS_DIR_BONUS)/file.c \
	$(SRCS_DIR_BONUS)/free.c \
	$(SRCS_DIR_BONUS)/init.c \
	$(SRCS_DIR_BONUS)/main.c \
	$(SRCS_DIR_BONUS)/map.c \
	$(SRCS_DIR_BONUS)/map_utils.c \
	$(SRCS_DIR_BONUS)/movement_bonus.c \
	$(SRCS_DIR_BONUS)/parse_color.c \
	$(SRCS_DIR_BONUS)/parse_config.c \
	$(SRCS_DIR_BONUS)/parse_map.c \
	$(SRCS_DIR_BONUS)/parse_texture.c \
	$(SRCS_DIR_BONUS)/parse_utils.c \
	$(SRCS_DIR_BONUS)/player.c \
	$(SRCS_DIR_BONUS)/queue.c \
	$(SRCS_DIR_BONUS)/ray.c \
	$(SRCS_DIR_BONUS)/ray_utils.c \
	$(SRCS_DIR_BONUS)/render.c \
	$(SRCS_DIR_BONUS)/rotation.c \
	$(SRCS_DIR_BONUS)/textures.c \
	$(SRCS_DIR_BONUS)/utils.c \
	$(SRCS_DIR_BONUS)/validation.c \

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
BONUS_OBJS = $(SRCS_BONUS:$(SRCS_DIR_BONUS)/%.c=$(OBJS_DIR_BONUS)/%.o)

# Rules
all: $(NAME)

# check CMake
check_cmake:
	@if ! command -v cmake >/dev/null 2>&1; then \
		echo "Error: CMake not found!"; \
		echo "Install it with:"; \
		echo "	Debian/Ubuntu: sudo apt-get install cmake"; \
		echo "	Arch: sudo pacman -S cmake"; \
		echo "	macOS: brew install cmake"; \
		exit 1; \
	else \
		echo "CMake found: $$(cmake --version | head -n1)"; \
	fi

# MLX42 clone
prepare_mlx:
	@if [ ! -f "$(MLX_DIR)/CMakeLists.txt" ]; then \
		echo "Initializing MLX42 submodule..."; \
		git submodule update --init --recursive; \
		echo "MLX42 submodule initialized"; \
	else \
		echo "MLX42 submodule already initialized"; \
	fi

# MLX42 build
mlx: check_cmake prepare_mlx
	@if [ ! -f "$(MLX_LIB)" ]; then \
		echo "Building MLX42..."; \
		cmake $(MLX_DIR) -B $(MLX_BUILD) && make -C $(MLX_BUILD) -j4; \
		echo "$(GREEN)MLX42 built.$(RESET)"; \
	fi

$(MLX_LIB):
	@make mlx

$(LIBFT):
	@make -C $(LIBFT_DIR) bonus
	@echo "$(GREEN)Libft DONE!$(RESET)"

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LDFLAGS) -o $(NAME)
	@echo "$(NEON_GREEN)Build DONE!$(RESET)"

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(MLX_LIB) $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) $(MLX_LDFLAGS) -o $(NAME_BONUS)
	@echo "$(NEON_GREEN)Bonus build DONE!$(RESET)"

# Compiling the object files
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR_BONUS)/%.o: $(SRCS_DIR_BONUS)/%.c
	@mkdir -p $(OBJS_DIR_BONUS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR) $(OBJS_DIR_BONUS)
	@make -C $(LIBFT_DIR) clean
	@echo "$(BLUE)Clean DONE!$(RESET)"

clean_mlx:
	@if [ -d "$(MLX_BUILD)" ]; then \
		rm -rf $(MLX_BUILD); \
		echo "$(BLUE)MLX42 build directory cleaned.$(RESET)"; \
	else \
		echo "MLX42 build directory doesn't exist."; \
	fi

fclean: clean clean_mlx
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(BLUE)Fclean DONE!$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus prepare_mlx mlx clean_mlx

