/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:22:54 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/10 18:24:51 by vdarsuye         ###   ########.fr       */
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
	int		i;
	size_t	max_width;
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

int	is_player_symbol(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}
