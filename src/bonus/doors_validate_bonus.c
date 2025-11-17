/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_validate_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 18:32:49 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/15 18:36:45 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	is_door_on_outer_wall(t_game *game, int x, int y)
{
	if (x == 0 || x == game->map.width - 1)
		return (1);
	if (y == 0 || y == game->map.height - 1)
		return (1);
	return (0);
}

int	validate_doors(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_doors)
	{
		if (is_door_on_outer_wall(game, game->doors[i].x, game->doors[i].y))
			return (error_msg("Invalid door"), 0);
		i++;
	}
	return (1);
}
