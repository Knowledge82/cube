/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:20:41 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/10/08 16:46:41 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUBE_H
# define CUBE_H

#include "libft.h"
#include "MLX42.h"
#include <unistd.h> //close
#include <stdio.h> //perror
#include <errno.h> //errno
#include <fcntl.h> //open
#include <math.h>

typedef struct	s_game
{
	mlx_t		*mlx;
	t_map		*map;
	t_texture	*textures;
	t_config	*config;
	t_player	*player;
}	t_game;

typedef struct	s_map
{
	char	**grid;
	int		width;
	int		heigth;
	int		player_x; // начальная позиция игрока по Х
	int		player_y; // начальная позиция игрока по Y
	char	player_dir; // направление (N/S/W/E)
}	t_map;

/*
typedef struct	s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	mlx_image_t	*img_n;
	mlx_image_t	*img_s;
	mlx_image_t	*img_w;
	mlx_image_t	*img_e;
}	t_texture;
*/

typedef struct	s_config
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor_color;  // 0xRRGGBB
	int		ceiling_color; // 0xRRGGBB
}	t_config;

typedef struct	s_player
{// dir и plane - векторы для алгоритма ray casting
	double	pos_x; // текущая Х позиция 
	double	pos_y; // текущая Y позиция 
	double	dir_x; // направление взгляда
	double	dir_y;
	double	plane_x; // плоскость камеры Х (перпендикулярна dir)
	double	plane_y;
}	t_player;

typedef struct	s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct	s_queue
{
	t_point	*data;
	int	first;
	int	last;
	int	current_size;
	int	capacity;
}	t_queue;

// FUNCS

// main.c
int init_game(const char *filename, t_config *config);

// file.c
char    **load_file_data(int fd);
char    **read_file(char *filename);

// parse.c
int parse_texture(char *line, t_config *config, char *id);
int parse_number(char *line, int *i);
int parse_color(char *line, t_config *config, char *id);
int parse_identifier(char *line, t_config *config);
int parse_config(char **file, int map_start, t_config *config);

// parse_utils.c
char    *get_identifier(char *line);
char    *extract_path(char *line, char *id);
int check_color_data_range(int r, int g, int b);
int file_exist(char *path);
int check_texture_file(char *path);
int validate_config(t_config *config);

// utils.c
void    error_msg(char *msg);
int     check_extension(const char *filename);

// validation.c
int is_map_symbol(char c);
int is_empty_line(char *line);
int is_map_line(char *line);
int find_map_start(char **file);


#endif

