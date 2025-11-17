/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 19:51:10 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/17 16:01:48 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	init_sprite_data(t_sprite *sprite, int x, int y)
{
	sprite->x = x + 0.5;
	sprite->y = y + 0.5;
	sprite->num_frames = 3;
	sprite->current_frame = 0;
	sprite->animation_timer = 0.0;
}

static int	count_sprites(t_game *game)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == 'X')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static int	fill_sprites_array(t_game *game)
{
	int	sprite_index;
	int	x;
	int	y;

	sprite_index = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == 'X')
			{
				init_sprite_data(&game->sprites[sprite_index], x, y);
				if (!load_sprite_textures(&game->sprites[sprite_index]))
					return (0);
				game->map.grid[y][x] = '0';
				sprite_index++;
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	init_sprite(t_game *game)
{
	game->num_sprites = count_sprites(game);
	if (game->num_sprites == 0)
		return (1);
	game->sprites = malloc(sizeof(t_sprite) * game->num_sprites);
	if (!game->sprites)
		return (0);
	if (!fill_sprites_array(game))
		return (0);
	return (1);
}
