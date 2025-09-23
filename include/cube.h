#ifndef CUBE_H
#define CUBE_H

#include <unistd.h>
//#include <>

typedef struct	s_game
{
	t_config	config;
	//MLX
	//textures
}	t_game;

typedef struct	s_texture
{
	void	*img;
	char	*path;
	int		width;
	int		height;
	int		*data;
}	t_texture;

typedef struct	s_config
{
	t_texture	*north;
	t_texture	*south;
	t_texture	*west;
	t_texture	*east;
	t_map		map;
	t_player	player;
	int		floor_color[3]; // RGB
	int		ceiling_color[3]; // RGB
	int		is_valid; // флаг валидности конфига
}	t_config;

typedef struct	s_map
{
	char	**data;
	int		width;
	int		height;
}	t_map;

typedef struct	s_player
{
	double	player_x;
	double	player_y;
	char	player_dir; // N,S,E,W
}	t_player;


#endif

