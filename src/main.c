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

void	init_game_structures(t_game *game) // название поменять.
{
	ft_memset(game, 0, sizeof(t_game)); // check

	// init config
	game->config->north = NULL;
	game->config->south = NULL;
	game->config->west = NULL;
	game->config->east = NULL;
	game->config->floor_color = -1;
	game->config->ceiling_color = -1;

	// init map
	game->map->grid = NULL;
	game->map->width = 0;
	game->map->heigth = 0;
}

int	init_game(const char *filename, t_config *config)
{
	char		**file;

	if (!check_extension(filename))
		return (error_msg("Wrong map file extension"), 0);
	file = read_file(filename);
	if (!file)
		return (error_msg("Cannot read map file"), 0);
	map_start = find_map_start(file);
	if (map_start == -1)
	{
		ft_free_array(file);
		return (error_msg("Map not found"), 0);
	}
	if (!parse_config(file, map_start, config))
	{
		ft_free_array(file);
		return (error_msg("Invalid map config"), 0);
	}
	if (!parse_map(file, config))
	{
		ft_free_array(file);
		free_config(&config)
		return (error_msg("Invalid map"), 0);
	}
	if (!init_mlx(config))
	{
		ft_free_array(file);
		free_config(config);
		return(0);
	}
	ft_free_array(file);
	return (1);
}

int	main(int argc, char **argv)
{
	t_config	config;

	if (argc != 2)
	{
		error_msg("Too many arguments");
		return 1;
	}

	if (!init_game(argv[1], &config))
	{
		error_msg("Game initialization failed");
		return 1;
	}

	run_game(&config);

	cleanup(&config);

	return (0);
}
