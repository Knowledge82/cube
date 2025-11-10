/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:55:40 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/10 14:13:33 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	handle_movement_w_s(t_game *game)
{
	double	new_x;
	double	new_y;

        if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		new_x = game->player.pos_x + game->player.dir_x * game->move_speed;
		new_y = game->player.pos_y + game->player.dir_y * game->move_speed;
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		new_x = game->player.pos_x - game->player.dir_x * game->move_speed;
		new_y = game->player.pos_y - game->player.dir_y * game->move_speed;
		game->player.pos_x = new_x;
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
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		new_x = game->player.pos_x + game->player.plane_x * game->move_speed;
		new_y = game->player.pos_y + game->player.plane_y * game->move_speed;
		game->player.pos_x = new_x;
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

void	clamp_player_position(t_game *game)//ограничение позиции игрока в пределах карты для предотвращения выхода игрока за границы. clamp = прижимать
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
