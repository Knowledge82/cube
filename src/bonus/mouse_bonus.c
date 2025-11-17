/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 12:08:03 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/16 19:46:32 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_mouse(t_game *game)
{
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	game->mouse.last_x = WIDTH / 2;
	game->mouse.last_y = HEIGHT / 2;
	mlx_set_mouse_pos(game->mlx, game->mouse.last_x, game->mouse.last_y);
}

void	handle_mouse_rotation(t_game *game)
{
	int		current_x;
	int		current_y;
	double	delta_x;
	double	rot_angle;

	mlx_get_mouse_pos(game->mlx, &current_x, &current_y);
	delta_x = current_x - game->mouse.last_x;
	if (delta_x == 0)
		return ;
	rot_angle = delta_x * MOUSE_SENSITIVITY;
	rotate_player(game, rot_angle);
	game->mouse.last_x = current_x;
}
