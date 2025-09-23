#ifndef CUBE_H
#define CUBE_H

#include <unistd.h>
//#include <>

typedef struct	s_game
{
	t_config	config;
	t_map		map;
	t_player	player;
	//MLX
	//textures
}	t_game;

typedef struct	s_config
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color[3]; // RGB
	int		ceiling_color[3]; // RGB
}	t_config;

typedef struct	s_map
{
	char	**grid;
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

