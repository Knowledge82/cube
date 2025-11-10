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

int	copy_map_line(char **map_grid, int index, const char *src, size_t target_width)
{
	char	*clean_line;
	size_t	clean_len;

	clean_line = ft_strtrim(src, "\n\r");
	if (!clean_line)
		return (0);
	if (ft_strchr(clean_line, '\t'))
		return (error_msg("Tab character in map. Use spaces."), free(clean_line), 0);
	map_grid[index] = ft_calloc(target_width + 1, sizeof(char));
	if (!map_grid[index])
		return (error_msg("Map memory allocation failed"), free(clean_line), 0);
	clean_len = ft_strlen(clean_line);
	ft_memcpy(map_grid[index], clean_line, clean_len);
	while (clean_len < target_width)
	{
		map_grid[index][clean_len] = ' ';
		clean_len++;
	}
	map_grid[index][target_width] = '\0';
	free(clean_line);
	return (1);
}

int	read_map(char **file, t_map *map)
{
	int	map_start;
	int	map_end;
	int	map_line;
	int	i;

	map_start = find_map_start(file);
	map_line = map_start;
	map->height = calculate_map_height(file);
	map->width = calculate_map_width(file, map_start);
	if (map->width <= 0)
		return (error_msg("Invalid map width"), 0);
	map_end = map_start + map->height;
	i = 0;
	if (!allocate_map_grid(map))
		return (0);
	while(map_line < map_end)
	{
		if (is_empty_line(file[map_line]))
		{
			free_grid(map->grid);
			return (error_msg("Empty line in the map"), 0);
		}
		if (!copy_map_line(map->grid, i, file[map_line], map->width))
			return (free_grid(map->grid), 0);
		map_line++;
		i++;
	}
	map->grid[i] = NULL;
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
				if (player_found)
					return (error_msg("Multiply player position"), 0);
				else
				{
					map->player_start.x = j;
					map->player_start.y = i;
					map->start_dir = map->grid[i][j];
					map->grid[i][j] = '0';
					player_found = 1;
				}
			}
			j++;
		}
		i++;
	}
	if (!player_found)
		return (error_msg("Player not found"), 0);
	return (1);
}


int	parse_map(char **file, t_map *map)
{
	if (!read_map(file, map))
		return (0);
	if (!find_player(map))
		return (free_grid(map->grid), 0);
	if (!check_map_closure(map))
		return (free_grid(map->grid), 0);
	return (1);
}
