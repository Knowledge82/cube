/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:12:49 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/12 14:28:30 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

mlx_texture_t	*select_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (game->textures.west);
		else
			return (game->textures.east);
	}
	else
	{
		if (ray->dir_y > 0)
			return (game->textures.north);
		else
			return (game->textures.south);
	}
}

int	calculate_tex_x(t_game *game, t_ray *ray, mlx_texture_t *texture)
{
	int		tex_x;
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x = wall_x - floor(wall_x);
	tex_x = (int)(wall_x * (double)texture->width);
	if (tex_x >= (int)texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

uint32_t	get_texture_color(mlx_texture_t *texture, int tex_x, int tex_y)
{
	int		index;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	if (tex_x < 0 || tex_x >= (int)texture->width
		|| tex_y < 0 || tex_y >= (int)texture->height)
		return (0x000000FF);
	index = (tex_y * texture->width + tex_x) * 4;
	r = texture->pixels[index + 0];
	g = texture->pixels[index + 1];
	b = texture->pixels[index + 2];
	a = texture->pixels[index + 3];
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
