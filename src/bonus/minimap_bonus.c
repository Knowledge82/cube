/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 12:07:17 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/16 19:44:53 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	draw_minimap_tile(mlx_image_t *img, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_TILE_SIZE)
	{
		j = 0;
		while (j < MINIMAP_TILE_SIZE)
		{
			if (x + j < (int)img->width && y + i < (int)img->height)
				mlx_put_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_minimap_border(mlx_image_t *img, int size)
{
	int	total_pixel_size;
	int	x;
	int	y;

	total_pixel_size = size * MINIMAP_TILE_SIZE;
	x = MINIMAP_OFFSET;
	while (x < MINIMAP_OFFSET + total_pixel_size)
	{
		mlx_put_pixel(img, x, MINIMAP_OFFSET, MINIMAP_COLOR_BORDER);
		mlx_put_pixel(img, x, MINIMAP_OFFSET + total_pixel_size - 1,
			MINIMAP_COLOR_BORDER);
		x++;
	}
	y = MINIMAP_OFFSET;
	while (y < MINIMAP_OFFSET + total_pixel_size)
	{
		mlx_put_pixel(img, MINIMAP_OFFSET, y, MINIMAP_COLOR_BORDER);
		mlx_put_pixel(img, MINIMAP_OFFSET + total_pixel_size - 1, y,
			MINIMAP_COLOR_BORDER);
		y++;
	}
}

static void	draw_minimap_player(mlx_image_t *img, int center_x, int center_y)
{
	int			i;
	int			j;
	int			player_size;

	player_size = MINIMAP_TILE_SIZE / 2;
	i = -player_size;
	while (i <= player_size)
	{
		j = -player_size;
		while (j <= player_size)
		{
			if (center_x + j >= 0 && center_x + j < (int)img->width
				&& center_y + i >= 0 && center_y + i < (int)img->height)
				mlx_put_pixel(img, center_x + j, center_y + i,
					MINIMAP_COLOR_PLAYER);
			j++;
		}
		i++;
	}
}

static void	draw_minimap_grid(t_game *game)
{
	int	i;
	int	j;
	int	map_x;
	int	map_y;

	i = -MINIMAP_RADIUS;
	while (i <= MINIMAP_RADIUS)
	{
		j = -MINIMAP_RADIUS;
		while (j <= MINIMAP_RADIUS)
		{
			map_x = (int)game->player.pos_x + j;
			map_y = (int)game->player.pos_y + i;
			draw_minimap_tile(game->image, get_screen_pos(j),
				get_screen_pos(i), get_tile_color(game, map_x, map_y));
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	center_x;
	int	center_y;

	draw_minimap_grid(game);
	draw_minimap_border(game->image, MINIMAP_RADIUS * 2 + 1);
	center_x = get_screen_pos(0) + MINIMAP_TILE_SIZE / 2;
	center_y = get_screen_pos(0) + MINIMAP_TILE_SIZE / 2;
	draw_minimap_player(game->image, center_x, center_y);
}
