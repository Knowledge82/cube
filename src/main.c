/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:47:55 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/10/08 16:21:30 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	init_game(char *filename, t_config *config)
{
	char		**file;

	if (!check_extension(filename))
	{
		print_error("Wrong map file extension");
		return 0;
	}
	file = read_file(filename);
	if (!file)
	{
		error("Cannot read map file");
		return (0);
	}
	if (!check_config(file, config))
	{
		free_file(file);
		error("Invalid map config");
		return 0;
	}
	if (!check_map(file, config))
	{
		free_file(file);
		free_config(&config)
		error("Invalid map");
		return 0;
	}
	free_file(file);
	return (1);
}

int	main(int argc, char **argv)
{
	t_config	config;

	if (argc > 1)
	{
		print_error("Too many arguments");
		return 1;
	}

	if (!init_game(argv[1], &config))
	{
		error("Game initialization failed");
		return 1;
	}

	run_game(&config);

	cleanup(&config);

	return (0);
}
