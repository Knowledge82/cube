#include "so_long.h"

int	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

int	is_valid_map(t_map *map)
{

}

int	check_borders(char **map, int width, int height)
{
	int	i;

	//проверка верхней и нижней границ
	i = 0;
	while (i < width)
	{
		if (map[0][i] != '1' || map[height - 1][i] != '1')
			return (0);
		i++;
	}

	//проверка боковых границ
	i = 0;
	while (i < height)
	{
		if (map[i][0] != '1' || map[i][width -1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_extension(const char *filename)
{
	int	len;
	len = ft_strlen(filename);
	
	if (len > 4 && ft_strncmp(filename + len - 4, ".cub", 4) == 0)
		return (1);
	else
		return (0);
	}
