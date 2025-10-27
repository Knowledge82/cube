# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 16:54:19 by vdarsuye          #+#    #+#              #
#    Updated: 2025/10/08 17:01:14 by vdarsuye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
#LDFLAGS = -L$(MLX_DIR)/build -lmlx42 -lglfw -lm -ldl -pthread

INCLUDES = -I$(SRC_DIR) -I$(LIBFT_DIR)

# Directories
SRC_DIR = src
SRC_DIR_BONUS = src/bonus
OBJ_DIR = obj
OBJ_DIR_BONUS = obj_bonus
LIBFT_DIR = ./libft
#MLX_DIR = ./MLX42

# Libs
LIBFT = $(LIBFT_DIR)/libft.a
#MLX_LIB = $(MLX_DIR)/build/libmlx42.a

# List of src files
SRC = $(SRC_DIR)/main.c \
	  $(SRC_DIR)/file.c \
	  $(SRC_DIR)/utils.c \
	  $(SRC_DIR)/map.c \
	  $(SRC_DIR)/queue.c \
	  $(SRC_DIR)/parse.c \
	  $(SRC_DIR)/parse_utils.c \
	  $(SRC_DIR)/bfs.c \
	  $(SRC_DIR)/validation.c \



#BONUS_SRC = $(SRC_DIR_BONUS)/ .c \

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
#BONUS_OBJS = 

# Rules
all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) bonus
	@echo "Libft DONE!"

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "Build DONE!"

#bonus: $(LIBFT) $(BONUS_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "Clean DONE!"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "Fclean DONE!"

re: fclean all

.PHONY: all clean fclean re bonus

