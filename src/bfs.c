#include "cube.h"

int	**create_visited(t_map *map)
{
	int **visited;
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
			while (j < i - 1)
				free(visited[i]);
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

int	is_valid_neighbor(int x, int y, t_map *map, int **visited) // на карте, не посещён
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	if (visited[y][x])
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

int	process_neighbor(t_map *map, int x, int y, t_queue *queue, int **visited)
{
	char	symbol;

	if (!is_valid_neighbor(x, y, map, visited))
		return (1);
	symbol = map->grid[y][x];
	if (symbol == ' ')
		return (0);
	if (symbol == '1')
		return (1);
	if (symbol == '0')
	{
		visited[y][x] = 1;
		enqueue(queue, create_point(x, y));
		return (1);
	}
	return (1);
}

int	validate_map_closure(t_map *map, t_point start_position)
{
	int	**visited;
	t_queue *queue;
	t_point current;
	int directions[4][2]; 
	int	new_x;
	int	new_y;

	directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	visited = create_visited(map);
	if (!visited)
		return (error_msg("Memory allocation on create visited failed"), 0);
	queue = create_queue(map->height * map->width);
	if (!queue)
		return (error_msg("Memory allocation on create queue failed"), 0);
	enqueue (queue, create_point(start_position.x, start_position.y));
	visited[start_position.y][start_position.x] = 1;
	while (!is_empty_queue(queue))
	{
		current = dequeue(queue);
		int	d = 0;
		while (d < 4)
		{
			new_x = current.x + directions[d][0]; // новая координата X
			new_y = current.y + directions[d][1]; // новая координата y
			if (!process_neighbor(map, new_x, new_y, queue, visited))
			{
				free_queue(queue);
				free_visited(visited, map->height);
				return (0);
			}
			d++;
		}
	}
	free_queue(queue);
	free_visited(visited, map->height)
	return (1);
}
