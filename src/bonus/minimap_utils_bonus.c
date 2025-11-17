/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 12:07:26 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/16 19:45:45 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
/*
	Принимает смещение относительно центра мини-карты
	(offset от -MINIMAP_RADIUS до +MINIMAP_RADIUS)
	Возвращает координату на экране в пикселях
*/
int	get_screen_pos(int offset)
{
	return (MINIMAP_OFFSET + (offset + MINIMAP_RADIUS) * MINIMAP_TILE_SIZE);
}

uint32_t	get_tile_color(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= game->map.width
		|| map_y < 0 || map_y >= game->map.height)
		return (MINIMAP_COLOR_EMPTY);
	if (game->map.grid[map_y][map_x] == '1')
		return (MINIMAP_COLOR_WALL);
	return (MINIMAP_COLOR_EMPTY);
}
