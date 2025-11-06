/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:55:40 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/06 16:40:36 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// проверяем, можно ли двигаться в позицию (x, y)
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

void	handle_movement_w_s(t_game *game)
{
	double	new_x;
	double	new_y;

        if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		new_x = game->player.pos_x + game->player.dir_x * game->move_speed;
		new_y = game->player.pos_y + game->player.dir_y * game->move_speed;
		// раздельные проверки по X и Y для скольжения вдоль стен
		// проверка коллизии по X
		if (can_move_to(game, new_x, game->player.pos_y))
			game->player.pos_x = new_x;
		// проверка коллизии по Y
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

void	handle_movement_a_d(t_game *game)
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

void	handle_rotation(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		cos_rot = cos(game->rotation_speed);
		sin_rot = sin(game->rotation_speed);

		// вращение вектора dir
		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos_rot - game->player.dir_y * sin_rot;
		game->player.dir_y = old_dir_x * sin_rot + game->player.dir_y * cos_rot;

		// вращение вектора plane
		old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos_rot - game->player.plane_y * sin_rot;
		game->player.plane_y = old_plane_x * sin_rot + game->player.plane_y * cos_rot;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		cos_rot = cos(game->rotation_speed * -1);
		sin_rot = sin(game->rotation_speed * -1);

		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos_rot - game->player.dir_y * sin_rot;
		game->player.dir_y = old_dir_x * sin_rot + game->player.dir_y * cos_rot;

		old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos_rot - game->player.plane_y * sin_rot;
		game->player.plane_y = old_plane_x * sin_rot + game->player.plane_y * cos_rot;
	}
}

void	handle_input(t_game *game)
{
	handle_movement_w_s(game);
	handle_movement_a_d(game);
	handle_rotation(game);
}
