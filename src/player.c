/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:30:43 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/10/30 18:12:20 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	init_player(t_player *player, t_map *map)
{
	player->pos_x = map->player_start.x + 0.5; // 0.5 = on center of the cell
	player->pos_y = map->player_start.y + 0.5;

	if (map->start_dir == 'N')
	{
		player->dir_x = 0; 
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (map->start_dir == 'S')
	{
		player->dir_x = 0; 
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (map->start_dir == 'W')
	{
		player->dir_x = -1; 
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
	else if (map->start_dir == 'E')
	{
		player->dir_x = 1; 
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	return (1);
}
