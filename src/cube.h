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
}	t_game;

typedef struct	s_map
{
	char	**map;
}	t_map;

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

typedef struct	s_config
{
	
}	t_config;

typedef struct	s_player
{
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	
}	t_player;

// FUNCS
// file.c
char    **load_file_data(int fd);
char    **read_file(char *filename);

// utils.c
int     is_valid_char(char c);
void    print_error(char *msg);
int     check_extension(const char *filename);


#endif

