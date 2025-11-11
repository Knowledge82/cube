/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:30:43 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/06 19:32:08 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
/* we use array in assign_direction() only by Norminette restriction
   of number of function arguments (4, and we have 5).
   Alternative way was create struct s_directions or substruct in s_player
*/
static void	assign_direction(t_player *player, const double *values)
{
	player->dir_x = values[0];
	player->dir_y = values[1];
	player->plane_x = values[2];
	player->plane_y = values[3];
}

int	init_player(t_player *player, t_map *map)
{
	player->pos_x = map->player_start.x + 0.5;
	player->pos_y = map->player_start.y + 0.5;
	if (map->start_dir == 'N')
		assign_direction(player, (double []){0, -1, 0.66, 0});
	else if (map->start_dir == 'S')
		assign_direction(player, (double []){0, 1, -0.66, 0});
	else if (map->start_dir == 'W')
		assign_direction(player, (double []){-1, 0, 0, -0.66});
	else if (map->start_dir == 'E')
		assign_direction(player, (double []){1, 0, 0, 0.66});
	return (1);
}
