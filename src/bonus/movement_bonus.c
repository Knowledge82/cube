/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:18:06 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/16 19:47:48 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	is_door_blocking(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->num_doors)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
		{
			if (game->doors[i].is_open == 0)
				return (1);
			return (0);
		}
		i++;
	}
	return (0);
}

int	can_move_to(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game->map.width
		|| map_y < 0 || map_y >= game->map.height)
		return (0);
	if (game->map.grid[map_y][map_x] == '1')
		return (0);
	if (game->map.grid[map_y][map_x] == 'D')
	{
		if (is_door_blocking(game, map_x, map_y))
			return (0);
	}
	return (1);
}

static void	handle_movement_w_s(t_game *game)
{
	double	new_x;
	double	new_y;

	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		new_x = game->player.pos_x + game->player.dir_x * game->move_speed;
		new_y = game->player.pos_y + game->player.dir_y * game->move_speed;
		if (can_move_to(game, new_x, game->player.pos_y))
			game->player.pos_x = new_x;
		if (can_move_to(game, game->player.pos_x, new_y))
			game->player.pos_y = new_y;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		new_x = game->player.pos_x - game->player.dir_x * game->move_speed;
		new_y = game->player.pos_y - game->player.dir_y * game->move_speed;
		if (can_move_to(game, new_x, game->player.pos_y))
			game->player.pos_x = new_x;
		if (can_move_to(game, game->player.pos_x, new_y))
			game->player.pos_y = new_y;
	}
}

static void	handle_movement_a_d(t_game *game)
{
	double	new_x;
	double	new_y;

	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		new_x = game->player.pos_x - game->player.plane_x * game->move_speed;
		new_y = game->player.pos_y - game->player.plane_y * game->move_speed;
		if (can_move_to(game, new_x, game->player.pos_y))
			game->player.pos_x = new_x;
		if (can_move_to(game, game->player.pos_x, new_y))
			game->player.pos_y = new_y;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		new_x = game->player.pos_x + game->player.plane_x * game->move_speed;
		new_y = game->player.pos_y + game->player.plane_y * game->move_speed;
		if (can_move_to(game, new_x, game->player.pos_y))
			game->player.pos_x = new_x;
		if (can_move_to(game, game->player.pos_x, new_y))
			game->player.pos_y = new_y;
	}
}

void	handle_input(t_game *game)
{
	handle_movement_w_s(game);
	handle_movement_a_d(game);
	handle_rotation(game);
}
