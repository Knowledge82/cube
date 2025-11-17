/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 12:06:57 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/16 18:13:00 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	cleanup(t_game *game)
{
	free_textures(&game->textures);
	if (game->map.grid)
		free_grid(game->map.grid);
	free_config(&game->config);
	if (game->doors)
	{
		free(game->doors);
		game->doors = NULL;
	}
	free_sprites(game);
	if (game->z_buffer)
	{
		free(game->z_buffer);
		game->z_buffer = NULL;
	}
	if (game->mlx)
		mlx_terminate(game->mlx);
}

void	free_sprites(t_game *game)
{
	int	i;
	int	j;

	if (!game->sprites)
		return ;
	i = 0;
	while (i < game->num_sprites)
	{
		if (game->sprites[i].frames)
		{
			j = 0;
			while (j < game->sprites[i].num_frames)
			{
				if (game->sprites[i].frames[j])
					mlx_delete_texture(game->sprites[i].frames[j]);
				j++;
			}
			free(game->sprites[i].frames);
		}
		i++;
	}
	free(game->sprites);
	game->sprites = NULL;
}

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		if (keydata.key == MLX_KEY_E)
			toggle_door(game);
	}
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_input(game);
	handle_mouse_rotation(game);
	update_sprite_animation(game);
	clamp_player_position(game);
	render_frame(game);
	render_sprites(game);
	draw_minimap(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (error_msg("Usage: ./cube3D <map.cub>"), 1);
	if (!init_game(argv[1], &game))
		return (1);
	if (!init_doors(&game))
		return (cleanup(&game), 1);
	if (!validate_doors(&game))
		return (cleanup(&game), 1);
	if (!init_engine(&game, WIDTH, HEIGHT))
		return (cleanup(&game), 1);
	if (!load_all_textures(&game.textures, &game.config))
		return (cleanup(&game), 1);
	if (!init_sprite(&game))
		return (cleanup(&game), 1);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_key_hook(game.mlx, &key_handler, &game);
	mlx_loop(game.mlx);
	cleanup(&game);
	return (0);
}
