/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:20:41 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/07 12:36:34 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUBE_H
# define CUBE_H
# define WIDTH 800
# define HEIGHT 600

#include "libft.h"
#include "MLX42.h"
#include <unistd.h> //close
#include <stdio.h> //perror
#include <errno.h> //errno
#include <fcntl.h> //open
#include <math.h> // fabs, INFINITY

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

typedef struct	s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;//расстояние луча, чтобы сдвинуться на 1.0 по Х
	double	delta_dist_y;//расстояние луча, чтобы сдвинуться на 1.0 по Y
	double	side_dist_x;// расстояние до след вертикальной границы
	double	side_dist_y;// расстояние до след горизонтальной границы
	int		step_x;// направление шага по X: +1 - вправо, -1 - влево
	int		step_y;// направление шага по Y: +1 - вних, -1 - вверх
	int		side; // какая граница пересечена: 0 - вертикальная, 1 - горизонтальная
	double	perp_wall_dist; // перпеникулярное расстояние до стены
}	t_ray;

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

typedef struct	s_wall_draw// это структура для хранения параметров отрисовки
{
	int	line_height;//высота стены на экране
	int	draw_start;//начало отрисовки стены(Y)
	int	draw_end;//конец отрисовки (Y)
	mlx_texture_t	*current_texture;// текущая текстура
	int	tex_x;//Х-координата на текстуре
	int	clipped_top;
}	t_wall_draw;

typedef struct	s_config
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	uint32_t	floor_color;  // 0xRRGGBBAA
	uint32_t	ceiling_color; // 0xRRGGBBAA
}	t_config;

typedef struct	s_player
{// dir и plane - векторы для алгоритма ray casting
	double	pos_x; // текущая Х позиция на карте (в клетках). стартовая позиция для луча
	double	pos_y; // текущая Y позиция 
	double	dir_x; // вектор направления взгляда
	double	dir_y;
	double	plane_x; // вектор плоскости камеры Х (|- dir, ~0.66). Поле зрения FOV.
	double	plane_y; // для вычисления направления каждого луча.
}	t_player;

typedef struct	s_game
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_config	config;
	t_map		map;
	t_textures	textures;
	t_player	player;
	double		move_speed;
	double		rotation_speed;
}	t_game;

typedef struct	s_queue
{
	t_point	*data;
	int	first;
	int	last;
	int	current_size;
	int	capacity;
}	t_queue;

// FUNCS
// movement.c
int     can_move_to(t_game *game, double x, double y);
void    handle_movement_w_s(t_game *game);
void    handle_movement_a_d(t_game *game);
void    handle_input(t_game *game);

// ray.c
void    init_ray(t_game *game, int x, t_ray *ray);
void    dda(t_game *game, t_ray *ray);
void    calculate_wall_distance(t_game *game, t_ray *ray);
void	render_frame(t_game *game);

// draw.c
void    init_draw_wall(t_game *game, t_ray *ray, t_wall_draw *wall);
void    draw_ceiling(t_game *game, int x, int draw_start);
void    draw_floor(t_game *game, int x, int draw_end);
void    draw_wall(t_game *game, int x, t_wall_draw *wall);
void    draw_column(t_game *game, int x, t_ray *ray);

// draw_utils.c
mlx_texture_t	*select_texture(t_game *game, t_ray *ray);
int		calculate_tex_x(t_game *game, t_ray *ray, mlx_texture_t *texture);
uint32_t	get_texture_color(mlx_texture_t *texture, int tex_x, int tex_y);

// textures.c
void	free_textures(t_textures *textures);
int	load_texture(mlx_texture_t **texture_field, const char *path);
int	load_all_textures(t_textures *textures, t_config *config);

// free.c
void    free_config(t_config *config);

// player.c
int init_player(t_player *player, t_map *map);


// main.c
void    init_game_data(t_game *game);
int		init_game(const char *filename, t_game *game);
void    cleanup(t_game *game);
int		init_engine(t_game *game, int width, int height);
void    key_handler(mlx_key_data_t keydata, void *param);
void    game_loop(void *param);

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
int calculate_map_width(char **file, int map_start);
int allocate_map_grid(t_map *map);
int copy_map_line(char **map_grid, int index, const char *src, size_t target_width);
int read_map(char **file, t_map *map);
int is_player_symbol(char c);
int find_player(t_map *map);
void    free_grid(char **grid);
int parse_map(char **file, t_map *map);

// bfs.c
int **create_visited(t_map *map);
void    free_visited(int **visited, int height);
int can_visit(t_point pos, t_map *map, int **visited);
t_point create_point(int x, int y);
int check_cell(t_map *map, t_point pos, t_queue *queue, int **visited);
int check_map_closure(t_map *map);

#endif

