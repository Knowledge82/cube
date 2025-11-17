/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:18:33 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/16 21:04:05 by pdoltu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_map_closure(t_map *map)
{
	t_bfs_data	*bfs;
	int			result;

	bfs = init_bfs(map);
	if (!bfs)
		return (0);
	result = process_bfs(map, bfs);
	free_queue(bfs->queue);
	free_visited(bfs->visited, map->height);
	free(bfs);
	return (result);
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
