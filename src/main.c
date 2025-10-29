/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:47:55 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/10/27 17:58:18 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
/*
void	print_map(t_map *map)
{
	printf("===== MAP GRID ======");
	printf("Width: %d, Height: %d\n", map->width, map->height);
	printf("Player start position: %d %d, direction: '%c'\n", map->player_start.x, map->player_start.y, map->start_dir);
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			char c = map->grid[i][j];
			if (c == ' ')
				printf("_");
			else if (c == '\n')
				printf("\\n");
			else if (c == '\0')
				printf("\\0");
			else
				printf("%c", c);
		}
		printf("\n");
	}
	printf("\n ============================ \n");
}
*/
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

	debug_log("INIT GAME:");
	init_game_data(game);
	debug_log("init game data ✅");
	if (!check_extension(filename))
		return (error_msg("Wrong map file extension"), 0);
	debug_log("check extension ✅");
	file = read_file(filename);
	if (!file)
		return (error_msg("Cannot read map file"), 0);
	debug_log("read file ✅");
	map_start = find_map_start(file);
	if (map_start == -1)
	{
		ft_free_array(file);
		return (error_msg("Map not found"), 0);
	}
	debug_log("find map start ✅");
	if (!parse_config(file, map_start, &game->config))
	{
		ft_free_array(file);
		free_config(&game->config);
		return (error_msg("Invalid map config"), 0);
	}
	debug_log("parse config ✅");
	if (!parse_map(file, &game->map))
	{
		ft_free_array(file);
		free_config(&game->config);
		return (error_msg("Invalid map"), 0);
	}
	debug_log("parse map ✅");
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
	free_config(&game->config);
/*	if (game->mlx)
		mlx_terminate(game->mlx);
*/
}

int	init_engine(t_data *data, int width, int height)
{
	data->mlx = mlx_init(width, height, "cube3D", false);
	if (!data->mlx)
		return (error_msg("MLX init failed"), 0);
	data->image = mlx_new_image(data->mlx, width, height);
	if (!data->image)
		return (error_msg("Image creation failed"), 0);
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) < 0)
		return (error_msg("Image to window failed"), 0);
	return (1);
}

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data*)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(data->mlx);
	}
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_data	data;

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
	
	if (!init_engine(&data, WIDTH, HEIGHT))
		return (cleanup(&game), 1);
	mlx_key_hook(data.mlx, &key_handler, &data);
	mlx_loop(data.mlx);

//	print_map(&game.map);
//	run_game(&game);

	cleanup(&game);

	return (0);
}

