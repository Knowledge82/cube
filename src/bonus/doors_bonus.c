/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 12:08:36 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/16 19:40:53 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	count_doors(t_game *game)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] == 'D')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static void	fill_doors_array(t_game *game)
{
	int	i;
	int	j;
	int	index;

	index = 0;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] == 'D')
			{
				game->doors[index].x = j;
				game->doors[index].y = i;
				game->doors[index].is_open = 0;
				index++;
			}
			j++;
		}
		i++;
	}
}

int	init_doors(t_game *game)
{
	game->num_doors = count_doors(game);
	if (game->num_doors == 0)
		return (1);
	game->doors = malloc(sizeof(t_door) * game->num_doors);
	if (!game->doors)
		return (0);
	fill_doors_array(game);
	return (1);
}

t_door	*find_door_at(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->num_doors)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (&game->doors[i]);
		i++;
	}
	return (NULL);
}

void	toggle_door(t_game *game)
{
	int		target_x;
	int		target_y;
	t_door	*door;

	target_x = (int)(game->player.pos_x + game->player.dir_x * 1.5);
	target_y = (int)(game->player.pos_y + game->player.dir_y * 1.5);
	if (target_x < 0 || target_x >= game->map.width
		|| target_y < 0 || target_y >= game->map.height)
		return ;
	if (game->map.grid[target_y][target_x] != 'D')
		return ;
	door = find_door_at(game, target_x, target_y);
	if (!door)
		return ;
	door->is_open = !door->is_open;
}
