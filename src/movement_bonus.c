/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:18:06 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/12 13:18:08 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
