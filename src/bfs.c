/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:48:21 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/10/30 11:48:23 by vdarsuye         ###   ########.fr       */
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

void	free_visited(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

int	can_visit(t_point pos, t_map *map, int **visited) // на карте, не посещён
{
	if (pos.x < 0 || pos.x >= map->width || pos.y < 0 || pos.y >= map->height)
		return (0);
	if (visited[pos.y][pos.x])
		return (0);
	return (1);
}

t_point	create_point(int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
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

int	check_map_closure(t_map *map)
{
	int		**visited;
	int		d;
	t_queue	*queue;
	t_point	current;
	t_point	new_pos;

	visited = create_visited(map);
	if (!visited)
		return (error_msg("Memory allocation on create visited failed"), 0);
	queue = create_queue(map->height * map->width);
	if (!queue)
	{
		free_visited(visited, map->height);
		return (error_msg("Memory allocation on create queue failed"), 0);
	}
	enqueue(queue, map->player_start);
	visited[map->player_start.y][map->player_start.x] = 1;
	while (!is_empty_queue(queue))
	{
		current = dequeue(queue);
		d = 0;
		while (d < 4)
		{
			new_pos = create_point(current.x + g_dx[d], current.y + g_dy[d]);
			if (!check_cell(map, new_pos, queue, visited))
			{
				free_queue(queue);
				free_visited(visited, map->height);
				return (0);
			}
			d++;
		}
	}
	free_queue(queue);
	free_visited(visited, map->height);
	return (1);
}
