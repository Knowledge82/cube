/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:48:08 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/10/30 15:29:47 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	free_textures(t_textures *textures)
{
	if (textures->north != NULL)
		mlx_delete_texture(textures->north);
	if (textures->south != NULL)
		mlx_delete_texture(textures->south);
	if (textures->west != NULL)
		mlx_delete_texture(textures->west);
	if (textures->east != NULL)
		mlx_delete_texture(textures->east);
}

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

	if (!load_texture(&textures->north, config->north)
		|| !load_texture(&textures->south, config->south)
	       	|| !load_texture(&textures->west, config->west)
	       	|| !load_texture(&textures->east, config->east))
		return (free_textures(textures), 0);
	return (1);
}

//mlx_texture_to_image   >mlx_image_t* mlx_texture_to_image(mlx_t* mlx, mlx_texture_t* texture)
