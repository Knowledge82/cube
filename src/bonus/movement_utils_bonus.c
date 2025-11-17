/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:48:03 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/16 19:48:30 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	clamp_player_position(t_game *game)
{
	double	min_x;
	double	max_x;
	double	min_y;
	double	max_y;

	min_x = 0.5;
	max_x = (double)game->map.width - 0.5;
	min_y = 0.5;
	max_y = (double)game->map.height - 0.5;
	if (game->player.pos_x < min_x)
		game->player.pos_x = min_x;
	if (game->player.pos_x > max_x)
		game->player.pos_x = max_x;
	if (game->player.pos_y < min_y)
		game->player.pos_y = min_y;
	if (game->player.pos_y > max_y)
		game->player.pos_y = max_y;
}
