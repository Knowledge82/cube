/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:48:21 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/10 15:25:20 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static const int	g_dx[4] = {0, 1, 0, -1};
static const int	g_dy[4] = {1, 0, -1, 0};

int	**create_visited(t_map *map)
{
	int	**visited;
	int	i;
	int	j;

	visited = malloc(sizeof(int *) * map->height);
	if (!visited)
		return (error_msg("BFS failed on create visited"), NULL);
	i = 0;
	while (i < map->height)
	{
		visited[i] = ft_calloc(map->width, sizeof(int));
		if (!visited[i])
		{
			j = 0;
			while (j < i)
			{
				free(visited[j]);
				j++;
			}
			free(visited);
			return (error_msg("BFS failed on create visited"), NULL);
		}
		i++;
	}
	return (visited);
}

int	can_visit(t_point pos, t_map *map, int **visited)
{
	if (pos.x < 0 || pos.x >= map->width || pos.y < 0 || pos.y >= map->height)
		return (0);
	if (visited[pos.y][pos.x])
		return (0);
	return (1);
}

int	check_cell(t_map *map, t_point pos, t_queue *queue, int **visited)
{
	char	symbol;

	if (!can_visit(pos, map, visited))
		return (1);
	symbol = map->grid[pos.y][pos.x];
	if (symbol == ' ')
		return (0);
	if (symbol == '1')
		return (1);
	if (symbol == '0')
	{
		visited[pos.y][pos.x] = 1;
		enqueue(queue, pos);
		return (1);
	}
	return (1);
}

t_bfs_data	*init_bfs(t_map *map)
{
	t_bfs_data	*bfs;

	bfs = (t_bfs_data *)malloc(sizeof (t_bfs_data));
	if (!bfs)
		return (NULL);
	bfs->visited = create_visited(map);
	if (!bfs->visited)
		return (free(bfs), NULL);
	bfs->queue = create_queue(map->height * map->width);
	if (!bfs->queue)
	{
		free_visited(bfs->visited, map->height);
		free(bfs);
		return (NULL);
	}
	enqueue(bfs->queue, map->player_start);
	bfs->visited[map->player_start.y][map->player_start.x] = 1;
	return (bfs);
}

int	process_bfs(t_map *map, t_bfs_data *bfs)
{
	t_point	current;
	t_point	new_pos;
	int		d;

	while (!is_empty_queue(bfs->queue))
	{
		current = dequeue(bfs->queue);
		d = 0;
		while (d < 4)
		{
			new_pos = create_point(current.x + g_dx[d], current.y + g_dy[d]);
			if (!check_cell(map, new_pos, bfs->queue, bfs->visited))
				return (0);
			d++;
		}
	}
	return (1);
}
