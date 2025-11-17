/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 18:08:18 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/17 15:04:10 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	render_frame(t_game *game)
{
	uint32_t	x;
	t_ray		ray;

	x = 0;
	while (x < game->image->width)
	{
		init_ray(game, x, &ray);
		dda(game, &ray);
		calculate_wall_distance(game, &ray);
		game->z_buffer[x] = ray.perp_wall_dist;
		draw_column(game, x, &ray);
		x++;
	}
}

void	render_sprites(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_sprites)
	{
		render_single_sprite(game, &game->sprites[i]);
		i++;
	}
}
