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

int	read_map(char **file, t_map *map)
{
	int	map_line;
	int	line_len;
	int	max_width;
	int	i;

	map->height = calculate_map_height(file);
	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (error_msg("Map memory allocation failed"), 0);
	i = 0;
	map_line = find_map_start(file);
	max_width = 0;
	while(file[map_line])
	{
		if (is_empty_line(file[map_line]))
		{
			free_map(map->grid);
			error_msg("Empty line in the map");
			return (0);
		}
		map->grid[i] = ft_strdup(file[map_line]);
		if (!map->grid[i])
		{
			free_map(map->grid);
			map->grid = NULL;
			return (error_msg("Map memory allocation failed"), 0);
		}
		line_len = ft_strlen(map->grid[i]);
		if (line_len > max_width)
			max_width = line_len;
		i++;
		map_line++;
	}
	map->grid[i] = NULL;
	map->width = max_width;
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
					map->player_x = j;
					map->player_y = i;
					map->player_dir = map->grid[i][j];
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

char	*normalized_line(const char *original, int target_width)
{
	char	*new_line;
	size_t	current_len;

	current_len = ft_strlen(original);
	if (current_len < target_width)
	{
		new_line = malloc(sizeof(char) * (target_width + 1));
		if (!new_line)
			return (NULL);
		ft_memcpy(new_line, original, current_len);
		while (current_len < target_width)
			new_line[current_len++] = ' ';
		new_line[target_width] = '\0';
	}
	else
		new_line = ft_strdup(original);
	return (new_line);
}

int	normalize_map_width(t_map *map)
{
	int	i;
	char	**new_grid;

	if (!map || !map->grid || map->height <= 0 || map->width <= 0)
		return (error_msg("Wrong map data"), 0);

	new_grid = ft_calloc(map->height + 1, sizeof(char*));
	if (!new_grid)
		return (error_msg("Mem alloc failed"), 0);
	i = 0;
	while (i < map->height)
	{
		new_grid[i] = normalized_line(map->grid[i], map->width);
		if (!new_grid[i])
		{
			free_grid(new_grid);
			return (error_msg("Mem alloc failed"), 0);
		}
		i++;
	}
	new_grid[i] = NULL;
	free_grid(map->grid);
	map->grid = new_grid;
	return (1);
}








int	parse_map()
{
	read_map();
	normalize_map_width();
	find_player();
	check_map_closure();
	return (1);
}
