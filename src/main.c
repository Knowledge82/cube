/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:47:55 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/17 14:55:02 by pdoltu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	cleanup(t_game *game)
{
	free_textures(&game->textures);
	if (game->map.grid)
		free_grid(game->map.grid);
	free_config(&game->config);
	if (game->mlx)
		mlx_terminate(game->mlx);
}

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
	}
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_input(game);
	clamp_player_position(game);
	render_frame(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (error_msg("Too many arguments! Use: ./cube3D <*.cub>"), 1);
	if (!init_game(argv[1], &game))
		return (1);
	if (!init_engine(&game, WIDTH, HEIGHT))
		return (cleanup(&game), 1);
	if (!load_all_textures(&game.textures, &game.config))
		return (cleanup(&game), 1);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_key_hook(game.mlx, &key_handler, &game);
	mlx_loop(game.mlx);
	cleanup(&game);
	return (0);
}
