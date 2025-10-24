#include "cube.h"

char	**create_visited(t_game)
{
	int **visited;
	visited = malloc(sizeof(int *) * game->map->height);
	i = 0;
	while (i < game->map->height)
	{
		visited[i] = ft_calloc(game->map->width, sizeof(int)); // Все клетки иначально не посещены
		i++;
	}
	return (visited);
}


// BFS, breadth-first search
int	bfs(t_game *game, t_point start_position)
{
	int	i;
	int j;

	
	// Создаём очередь для BFS
	t_queue *queue;
	queue = create_queue(game->map->height * game->map->width);
	enqueue (queue, (t_point){start_position.x, start_position.y});
	visited[start_position.y][start_position.x] = 1;

	// Основной цикл BFS
	while (!is_empty_queue(queue))
	{
		t_point current;
		
		current = dequeue(queue);
		// Массив направлений
		int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
		int	d = 0;
		while (d < 4)
		{
			int	new_x = current.x + directions[d][0]; // новая координата X
			int new_y = current.y + directions[d][1]; // новая координата y

			// Проверяем, что сосед находится в пределах карты, не посещён и не является стеной
			if (new_x >= 0 && new_x <= game->map->width && new_y >= 0 && new_y <= game->map->height && !visited[new_y][new_x] && game->map->data[new_y][new_x] != '1')
			{
				visited[new_y][new_x] = 1;
				enqueue(queue, (t_point){new_x, new_y});

				if (game->map->data[new_y][new_x] == 'C')
					collectibles--;
				if (game->map->data[new_y][new_x] == 'E')
					exit_found = 1;

				// Если все цели достигнуты, завершаем поиск
				if (collectibles == 0 && exit_found)
				{
					free_queue(queue);
					i = 0;
					while (i < game->map->height)
					{
						free(visited[i]);
						i++;
					}
					free(visited);
					return (1); // путь найден
				}
			}
			d++;
		}
	}
	// Если поиск завершился, но цели не достигнуты
	free_queue(queue);
	i = 0;
	while (i < game->map->height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
	return (0); // путь не найден
}
