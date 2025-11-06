/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:48:08 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/06 17:53:18 by vdarsuye         ###   ########.fr       */
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

mlx_texture_t	*select_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0) // вертикальная стена (X-стена)
	{
		if (ray->dir_x > 0)
			return (game->textures.west);// луч вправо = смотрим на западную сторону
		else
			return (game->textures.east);// луч влево = смотрим на восточную
	}
	else // горизнтальная граница (Y-стена)
	{
		if (ray->dir_y > 0)
			return (game->textures.north);// луч вниз = смотрим на северную сторону
		else
			return (game->textures.south);// луч влево = смотрим на южную
		
	}
}

// Вычисление координаты Х на текстуре (где именно на стене попали)
int	calculate_tex_x(t_game *game, t_ray *ray, mlx_texture_t *texture)
{
	double	wall_x;
	int	tex_x;

	// координата точки пересечения на стене
	if (ray->side == 0) // если вертикальная стена
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else // горизонтальная
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;

	// берём только дробную часть (от 0.0 до 1.0)
	wall_x = wall_x - floor(wall_x);

	// масштабируем на ширину текстуры
	tex_x = (int)(wall_x * (double)texture->width);

	// защита от выхода за границы (на случай ошибок округления)
	if (tex_x >= (int)texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}
