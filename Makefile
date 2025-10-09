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
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

LIBFT = libft/libft.a

SRC_DIR = src
SRC_DIR_BONUS = src/bonus
OBJ_DIR = obj
OBJ_DIR_BONUS = obj_bonus

# List of src files
SRC = $(SRC_DIR)/main.c  \
SRC = $(SRC_DIR)/file.c  \
SRC = $(SRC_DIR)/utils.c  \
SRC = $(SRC_DIR)/validation.c  \



#BONUS_SRC = $(SRC_DIR_BONUS)/ .c \


