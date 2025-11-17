/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:23:58 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/17 18:45:19 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_game_data(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->move_speed = 0.05;
	game->rotation_speed = 0.02;
	game->config.north = NULL;
	game->config.south = NULL;
	game->config.west = NULL;
	game->config.east = NULL;
	game->config.floor_color = 0xFFFFFFFF;
	game->config.ceiling_color = 0xFFFFFFFF;
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

	init_game_data(game);
	if (!check_extension(filename))
		return (error_msg("Wrong map file extension"), 0);
	file = read_file(filename);
	if (!file)
		return (error_msg("Cannot read map file"), 0);
	map_start = find_map_start(file);
	if (map_start == -1)
		return (ft_free_array(file), error_msg("Map not found"), 0);
	else if (map_start == -2)
		return (ft_free_array(file),
			error_msg("Tab character in map. Use spaces."), 0);
	if (!parse_config(file, map_start, &game->config))
		return (ft_free_array(file), free_config(&game->config), 0);
	if (!parse_map(file, &game->map))
		return (ft_free_array(file), free_config(&game->config), 0);
	if (!init_player(&game->player, &game->map))
		return (0);
	ft_free_array(file);
	return (1);
}

int	init_engine(t_game *game, int width, int height)
{
	game->mlx = mlx_init(width, height, "cube3D", false);
	if (!game->mlx)
		return (error_msg("MLX init failed"), 0);
	game->image = mlx_new_image(game->mlx, width, height);
	if (!game->image)
		return (error_msg("Image creation failed"), 0);
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) < 0)
		return (error_msg("Image to window failed"), 0);
	return (1);
}
