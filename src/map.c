/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:31:38 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/10 18:30:01 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	init_map(char **file, t_map *map, int map_start)
{
	map->height = calculate_map_height(file);
	map->width = calculate_map_width(file, map_start);
	if (map->width <= 0)
		return (error_msg("Invalid map width"), 0);
	if (!allocate_map_grid(map))
		return (0);
	return (1);
}

static int	fill_map_grid(char **file, t_map *map, int map_start)
{
	int	map_end;
	int	map_line;
	int	i;

	map_end = map_start + map->height;
	map_line = map_start;
	i = 0;
	while (map_line < map_end)
	{
		if (is_empty_line(file[map_line]))
			return (error_msg("Empty line in the map"),
				free_grid(map->grid), 0);
		if (!copy_map_line(map->grid, i, file[map_line], map->width))
		{
			free_grid(map->grid);
			return (0);
		}
		map_line++;
		i++;
	}
	map->grid[i] = NULL;
	return (1);
}

int	read_map(char **file, t_map *map)
{
	int	map_start;

	map_start = find_map_start(file);
	if (!init_map(file, map, map_start))
		return (0);
	if (!fill_map_grid(file, map, map_start))
	{
		free_grid(map->grid);
		return (0);
	}
	return (1);
}

static int	set_player_start(t_map *map, int i, int j, int *player_found)
{
	if (*player_found)
		return (error_msg("Multiply player position"), 0);
	else
	{
		map->player_start.x = j;
		map->player_start.y = i;
		map->start_dir = map->grid[i][j];
		map->grid[i][j] = '0';
		*player_found = 1;
	}
	return (1);
}

int	find_player(t_map *map)
{
	int	i;
	int	j;
	int	player_found;

	player_found = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (is_player_symbol(map->grid[i][j]))
			{
				if (!set_player_start(map, i, j, &player_found))
					return (0);
			}
			j++;
		}
		i++;
	}
	if (!player_found)
		return (error_msg("Player not found"), 0);
	return (1);
}
