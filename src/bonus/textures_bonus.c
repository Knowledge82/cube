/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:06:45 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/16 20:48:11 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	load_texture(mlx_texture_t **texture_field, const char *path)
{
	mlx_texture_t	*tmp;

	tmp = mlx_load_png(path);
	if (!tmp)
		return (error_msg("Failed to load texture"), 0);
	*texture_field = tmp;
	return (1);
}

int	load_all_textures(t_textures *textures, t_config *config)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->door = NULL;
	if (!load_texture(&textures->north, config->north)
		|| !load_texture(&textures->south, config->south)
		|| !load_texture(&textures->west, config->west)
		|| !load_texture(&textures->east, config->east)
		|| !load_texture(&textures->door, config->door))
		return (free_textures(textures), 0);
	return (1);
}

int	load_sprite_textures(t_sprite *sprite)
{
	int	i;

	sprite->frames = malloc(sizeof(mlx_texture_t *) * sprite->num_frames);
	if (!sprite->frames)
		return (0);
	sprite->frames[0] = mlx_load_png("./textures/hui_1.png");
	sprite->frames[1] = mlx_load_png("./textures/hui_2.png");
	sprite->frames[2] = mlx_load_png("./textures/hui_3.png");
	i = 0;
	while (i < sprite->num_frames)
	{
		if (!sprite->frames[i])
			return (error_msg("Failed to load sprite frame"), 0);
		i++;
	}
	return (1);
}
