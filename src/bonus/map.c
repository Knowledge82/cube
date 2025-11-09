/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:31:38 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/06 12:31:39 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	calculate_map_height(char **file)
{
	int	start;
	int	end;

	start = find_map_start(file);
	if (start == -1)
		return (error_msg("Map parse failed"), -1);
	end = start;
	while (file[end])
		end++;
	return (end - start);
}

int	calculate_map_width(char **file, int map_start)
{
	size_t	max_width;
	int	i;
	char	*line;
	size_t	len;

	i = map_start;
	max_width = 0;
	while (file[i])
	{
		line = ft_strtrim(file[i], "\n\r");
		if (!line)
			return (error_msg("Memory allocation failed"), -1);
		len = ft_strlen(line);
		if (len > max_width)
			max_width = len;
		free(line);
		i++;
	}
	return (max_width);
}

int	allocate_map_grid(t_map *map)
{
	if (map->height <= 0)
		return (error_msg("Invalid map height"), 0);
	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (error_msg("Map memory allocation failed"), 0);
	return (1);
}

int	copy_map_line(char **map_grid, int index, const char *src, size_t target_width)
{
	char	*clean_line;
	size_t	clean_len;

	clean_line = ft_strtrim(src, "\n\r");
	if (!clean_line)
		return (0);
	if (ft_strchr(clean_line, '\t'))
	{
		free(clean_line);
		return (error_msg("Tab character in map. Use spaces."), 0);
	}
	map_grid[index] = ft_calloc(target_width + 1, sizeof(char));
	if (!map_grid[index])
	{
		free(clean_line);
		return (error_msg("Map memory allocation failed"), 0);
	}
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

int	is_player_symbol(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
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


void	free_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
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
