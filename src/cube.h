/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:20:41 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/17 17:18:04 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# define WIDTH 1920
# define HEIGHT 1080
# ifdef BONUS
#  define MINIMAP_TILE_SIZE 15
#  define MINIMAP_RADIUS 8
#  define MINIMAP_OFFSET 20

#  define MINIMAP_COLOR_WALL 0x808080FF //gray
#  define MINIMAP_COLOR_EMPTY 0xE0E0E0FF //light gray
#  define MINIMAP_COLOR_PLAYER 0xFF0000FF //red
#  define MINIMAP_COLOR_BORDER 0x000000FF //black
#  define MOUSE_SENSITIVITY 0.001
# endif

# include "libft.h"
# include "MLX42.h"
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
}	t_ray;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_door
{
	int	x;
	int	y;
	int	is_open;
}	t_door;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	t_point	player_start;
	char	start_dir;
}	t_map;

typedef struct s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	mlx_texture_t	*door;
}	t_textures;

typedef struct s_sprite
{
	double			x;
	double			y;
	mlx_texture_t	**frames;
	int				num_frames;
	int				current_frame;
	double			animation_timer;
}	t_sprite;

typedef struct s_sprite_transform
{
	double		sprite_x;
	double		sprite_y;
	double		transform_x;
	double		transform_y;
}	t_sprite_transform;

typedef struct s_sprite_view
{
	int	screen_x;
	int	height;
	int	width;
	int	start_x;
	int	end_x;
	int	start_y;
	int	end_y;
}	t_sprite_view;

typedef struct s_sprite_render_data
{
	t_sprite_transform	*transform;
	t_sprite_view		*view;
}	t_sprite_render_data;

typedef struct s_wall_draw
{
	mlx_texture_t	*current_texture;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_x;
	int				clipped_top;
}	t_wall_draw;

typedef struct s_config
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*door;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
}	t_config;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_mouse
{
	int	last_x;
	int	last_y;
}	t_mouse;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_config	config;
	t_map		map;
	t_textures	textures;
	t_player	player;
	t_mouse		mouse;
	double		move_speed;
	double		rotation_speed;
	int			num_doors;
	t_door		*doors;
	int			num_sprites;
	t_sprite	*sprites;
	double		*z_buffer;
}	t_game;

typedef struct s_queue
{
	t_point	*data;
	int		first;
	int		last;
	int		current_size;
	int		capacity;
}	t_queue;

typedef struct s_bfs_data
{
	int		**visited;
	t_queue	*queue;
}	t_bfs_data;

// FUNCS
// +init.c
void			init_game_data(t_game *game);
int				init_game(const char *filename, t_game *game);
int				init_engine(t_game *game, int width, int height);

// +rotation.c
void			handle_rotation(t_game *game);
void			rotate_player(t_game *game, double angle);

// +movement.c
void			handle_input(t_game *game);
void			clamp_player_position(t_game *game);

// +ray.c
void			init_ray(t_game *game, int x, t_ray *ray);
void			dda(t_game *game, t_ray *ray);
void			calculate_wall_distance(t_game *game, t_ray *ray);

// ray_utils.c
void			calculate_delta_dist(t_ray *ray);
void			init_step_and_side_dist(t_game *game, t_ray *ray);

// +render.c
void			render_frame(t_game *game);

// +draw.c
void			draw_column(t_game *game, int x, t_ray *ray);

// +draw_utils.c
mlx_texture_t	*select_texture(t_game *game, t_ray *ray);
uint32_t		get_texture_color(mlx_texture_t *texture, int tex_x, int tex_y);
int				calculate_tex_x(t_game *game, t_ray *ray,
					mlx_texture_t *texture);

// +textures.c
int				load_texture(mlx_texture_t **texture_field, const char *path);
int				load_all_textures(t_textures *textures, t_config *config);
int				load_sprite_textures(t_sprite *sprite);

// +free.c
void			free_config(t_config *config);
void			free_visited(int **visited, int height);
void			free_queue(t_queue *queue);
void			free_grid(char **grid);
void			free_textures(t_textures *textures);

// +player.c
int				init_player(t_player *player, t_map *map);

// +main.c
void			cleanup(t_game *game);
void			key_handler(mlx_key_data_t keydata, void *param);
void			game_loop(void *param);

// +file.c
char			**read_file(const char *filename);

// +parse_color.c
int				parse_color(char *line, t_config *config, char *id);

// +parse_config.c
int				parse_config(char **file, int map_start, t_config *config);

// +parse_map.c
int				check_map_closure(t_map *map);
int				parse_map(char **file, t_map *map);

// +parse_texture.c
int				parse_texture(char *line, t_config *config, char *id);

// +parse_utils.c
char			*get_identifier(char *line);
int				check_color_data_range(int r, int g, int b);
bool			file_exist(char *path);
int				validate_config(t_config *config);

// +utils.c
void			error_msg(char *msg);
int				check_extension(const char *filename);

// +validation.c
int				is_map_symbol(char c);
int				is_empty_line(char *line);
int				is_map_line(char *line);
int				find_map_start(char **file);

// +queue.c
t_queue			*create_queue(int capacity);
void			enqueue(t_queue *queue, t_point point);
t_point			dequeue(t_queue *queue);
int				is_empty_queue(t_queue *queue);
t_point			create_point(int x, int y);

// +map.c
int				read_map(char **file, t_map *map);
int				find_player(t_map *map);

// +map_utils.c
int				copy_map_line(char **map_grid, int index,
					const char *src, size_t target_width);
int				calculate_map_height(char **file);
int				calculate_map_width(char **file, int map_start);
int				allocate_map_grid(t_map *map);
int				is_player_symbol(char c);

// +bfs.c
t_bfs_data		*init_bfs(t_map *map);
int				process_bfs(t_map *map, t_bfs_data *bfs);
int				**create_visited(t_map *map);
int				can_visit(t_point pos, t_map *map, int **visited);
int				check_cell(t_map *map, t_point pos,
					t_queue *queue, int **visited);

# ifdef BONUS
// movement_bonus.c
int				can_move_to(t_game *game, double x, double y);
void			handle_input(t_game *game);

// movement_utils_bonus.c
void			clamp_player_position(t_game *game);

// +init_bonus.c
void			init_game_data(t_game *game);
int				init_game(const char *filename, t_game *game);
int				init_engine(t_game *game, int width, int height);

// +main_bonus.c
void			cleanup(t_game *game);
void			free_sprites(t_game *game);
void			key_handler(mlx_key_data_t keydata, void *param);
void			game_loop(void *param);

// validation_bonus
int				is_map_symbol(char c);
int				is_empty_line(char *line);
int				is_map_line(char *line);
int				find_map_start(char **file);

// +free_bonus.c
void			free_config(t_config *config);
void			free_visited(int **visited, int height);
void			free_queue(t_queue *queue);
void			free_grid(char **grid);
void			free_textures(t_textures *textures);

// +ray_bonus.c
void			init_ray(t_game *game, int x, t_ray *ray);
void			dda(t_game *game, t_ray *ray);
void			calculate_wall_distance(t_game *game, t_ray *ray);

// +minimap_bonus.c
void			draw_minimap(t_game *game);

// +minimap_utils_bonus.c
int				get_screen_pos(int offset);
uint32_t		get_tile_color(t_game *game, int map_x, int map_y);

// +mouse_bonus.c
void			init_mouse(t_game *game);
void			handle_mouse_rotation(t_game *game);

// textures_bonus.c
int				load_texture(mlx_texture_t **texture_field, const char *path);
int				load_all_textures(t_textures *textures, t_config *config);
int				load_sprite_textures(t_sprite *sprite);

// +parse_texture_bonus.c
int				parse_texture(char *line, t_config *config, char *id);

// +parse_utils_bonus.c
char			*get_identifier(char *line);
bool			file_exist(char *path);
int				validate_config(t_config *config);
int				check_color_data_range(int r, int g, int b);

// +door_bonus.c
int				init_doors(t_game *game);
t_door			*find_door_at(t_game *game, int x, int y);
void			toggle_door(t_game *game);

// +doors_validate_bonus.c
int				validate_doors(t_game *game);

// +sprite_bonus.c
int				init_sprite(t_game *game);

// +sprite_draw_bonus.c
void			update_sprite_animation(t_game *game);
void			draw_sprite_column(t_game *game, t_sprite *sprite,
					int x, t_sprite_render_data *data);

// +draw_utils_bonus.c
mlx_texture_t	*select_texture(t_game *game, t_ray *ray);
int				calculate_tex_x(t_game *game, t_ray *ray,
					mlx_texture_t *texture);
uint32_t		get_texture_color(mlx_texture_t *texture, int tex_x, int tex_y);

// +render_bonus.c
void			render_frame(t_game *game);
void			render_sprites(t_game *game);

// +render_sprite_bonus.c
void			render_single_sprite(t_game *game, t_sprite *sprite);
# endif

#endif
