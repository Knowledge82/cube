# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 16:54:19 by vdarsuye          #+#    #+#              #
#    Updated: 2025/10/30 11:18:02 by vdarsuye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Vars
NAME = cub3D
NAME_BONUS = cub3D_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

# Dirs
SRC_DIR = src
SRC_DIR_BONUS = src/bonus
OBJ_DIR = obj
OBJ_DIR_BONUS = obj_bonus
LIBFT_DIR = ./libft
MLX_DIR = ./MLX42
MLX_BUILD = $(MLX_DIR)/build

# Libs
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_BUILD)/libmlx42.a

# Headers
INCLUDES = -I$(SRC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)/include/MLX42

# Linker flags
MLX_LDFLAGS = $(MLX_LIB) -lglfw -lm -ldl -pthread

# Src files
SRC = $(SRC_DIR)/main.c \
	  $(SRC_DIR)/file.c \
	  $(SRC_DIR)/utils.c \
	  $(SRC_DIR)/map.c \
	  $(SRC_DIR)/queue.c \
	  $(SRC_DIR)/parse.c \
	  $(SRC_DIR)/parse_utils.c \
	  $(SRC_DIR)/bfs.c \
	  $(SRC_DIR)/validation.c \
	  $(SRC_DIR)/free.c \
	  $(SRC_DIR)/draw.c \
	  $(SRC_DIR)/player.c \



#BONUS_SRC = $(SRC_DIR_BONUS)/ .c \

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
#BONUS_OBJS = 

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

# check GLFW library
#check_glfw:
#	@if ! pkg-config --exist glfw3 2>/dev/null; then \
#		echo "Error: GLFW3 not found!"; \
#		echo "Install it with:"; \
#		echo "	Debian/Ubuntu: sudo apt-get install libglfw3-dev"; \
#		exit 1; \
#	else \
#		echo "GLFW3 found!"; \
#	fi

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
		echo "MLX42 built."; \
	fi

$(MLX_LIB):
	@make mlx

$(LIBFT):
	@make -C $(LIBFT_DIR) bonus
	@echo "Libft DONE!"

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_LDFLAGS) -o $(NAME)
	@echo "Build DONE!"

#bonus: $(LIBFT) $(BONUS_NAME)

# Compiling the object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "Clean DONE!"

clean_mlx:
	@if [ -d "$(MLX_BUILD)" ]; then \
		rm -rf $(MLX_BUILD); \
		echo "MLX42 build directory cleaned."; \
	else \
		echo "MLX42 build directory doesn't exist."; \
	fi

fclean: clean clean_mlx
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "Fclean DONE!"

re: fclean all

.PHONY: all clean fclean re bonus prepare_mlx mlx clean_mlx

