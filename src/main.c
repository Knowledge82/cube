/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:47:55 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/10/09 13:51:41 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_game_data(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));

	// init config
	game->config.north = NULL;
	game->config.south = NULL;
	game->config.west = NULL;
	game->config.east = NULL;
	game->config.floor_color = -1;
	game->config.ceiling_color = -1;

	// init map
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.player_start.x = 0;
	game->map.player_start.y = 0;
	game->map.start_dir = '\0';
}

int	init_game(const char *filename, t_game *game)
{
	char	**file;
	int		map_start;

	printf("INIT GAME\n");
	init_game_data(game);
	if (!check_extension(filename))
		return (error_msg("Wrong map file extension"), 0);
	printf("check extension - DONE!\n");
	file = read_file(filename);
	if (!file)
		return (error_msg("Cannot read map file"), 0);
	printf("read file - DONE!\n");
	map_start = find_map_start(file);
	if (map_start == -1)
	{
		ft_free_array(file);
		return (error_msg("Map not found"), 0);
	}
	printf("find map start - DONE!\n");
	if (!parse_config(file, map_start, &game->config))
	{
		ft_free_array(file);
		return (error_msg("Invalid map config"), 0);
	}
	printf("parse config - DONE!\n");
	if (!parse_map(file, &game->map))
	{
		ft_free_array(file);
		//free_config(&game->config);
		return (error_msg("Invalid map"), 0);
	}
	printf("parse map - DONE!\n");
/*	if (!init_mlx(config))
	{
		ft_free_array(file);
		free_config(config);
		return(0);
	}
*/
	ft_free_array(file);
	return (1);
}

void	cleanup(t_game *game)
{
	if (game->map.grid)
		free_grid(game->map.grid);
	if (game->config.north)
		free(game->config.north);
	if (game->config.south)
		free(game->config.south);
	if (game->config.west)
		free(game->config.west);
	if (game->config.east)
		free(game->config.east);
/*	if (game->mlx)
		mlx_terminate(game->mlx);
*/
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		error_msg("Usage: ./cube3D <map.cub>");
		return (1);
	}

	if (!init_game(argv[1], &game))
	{
		error_msg("Game initialization failed");
		return (1);
	}

//	run_game(&game);

	cleanup(&game);

	return (0);
}

