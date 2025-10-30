/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:20:41 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/10/30 17:54:10 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUBE_H
# define CUBE_H
# define WIDTH 1280
# define HEIGHT 720

#include "libft.h"
#include "MLX42.h"
#include <unistd.h> //close
#include <stdio.h> //perror
#include <errno.h> //errno
#include <fcntl.h> //open
#include <math.h>

//====================================================================
// VARIADIC MACRO for debug log
// ##__VA_ARGS__ это "подставь все оставшиеся аргументы, если они есть" и ## убирает запятую, если аргументов нет
//чтобы отключить

/*# define debug_log(fmt, ...) ((void)0)*/

//короткий вывод
# define debug_log(fmt, ...) \
	dprintf(2, "DEBUG LOG: " fmt "\n", ##__VA_ARGS__)


//полный вывод
/*# define debug_log(fmt, ...) \
	dprintf(2, "[%s:%d %s]: " fmt "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)*/
//====================================================================

typedef struct	s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct	s_map
{
	char	**grid;
	int		width;
	int		height;
	t_point	player_start;
	char	start_dir; // направление (N/S/W/E)
}	t_map;

typedef struct	s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
}	t_textures;

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

typedef struct	s_game
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_config	config;
	t_map		map;
	t_textures	textures;
	t_player	player;
}	t_game;

typedef struct	s_queue
{
	t_point	*data;
	int	first;
	int	last;
	int	current_size;
	int	capacity;
}	t_queue;

typedef struct	s_data
{
	mlx_t		*mlx; // окно
	mlx_image_t	*image; // изображение для рендеринга
	t_game		*game;
}	t_data;

// FUNCS
// free.c
void    free_config(t_config *config);


// main.c
void    init_game_data(t_game *game);
int		init_game(const char *filename, t_game *game);

// file.c
char    **load_file_data(int fd);
char    **read_file(const char *filename);

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
bool file_exist(char *path);
int validate_config(t_config *config);

// utils.c
void    error_msg(char *msg);
int     check_extension(const char *filename);

// validation.c
int is_map_symbol(char c);
int is_empty_line(char *line);
int is_map_line(char *line);
int find_map_start(char **file);

// queue.c
t_queue *create_queue(int capacity);
void    enqueue(t_queue *queue, t_point point);
t_point dequeue(t_queue *queue);
int is_empty_queue(t_queue *queue);
void    free_queue(t_queue *queue);

// map.c
int calculate_map_height(char **file);
int read_map(char **file, t_map *map);
int is_player_symbol(char c);
int find_player(t_map *map);
void    free_grid(char **grid);
char    *normalized_line(const char *original, size_t target_width);
int normalize_map_width(t_map *map);
int parse_map(char **file, t_map *map);

// bfs.c
int **create_visited(t_map *map);
void    free_visited(int **visited, int height);
int can_visit(t_point pos, t_map *map, int **visited);
t_point create_point(int x, int y);
int check_cell(t_map *map, t_point pos, t_queue *queue, int **visited);
int check_map_closure(t_map *map);

#endif

