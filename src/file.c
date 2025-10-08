/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:59:39 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/10/08 15:01:38 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
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
*/

int	check_extension(const char *filename)
{
	int	len;
	len = ft_strlen(filename);
	
	if (len > 4 && ft_strncmp(filename + len - 4, ".cub", 4) == 0)
		return (1);
	else
		return (0);
}

char	**load_file_data(int fd)
{
	char	**file;
	char	**temp;
	char	*line;
	int	count;
	
	file = NULL;
	count = 0;
	while((line = get_next_line(fd)) != NULL)
	{
		temp = ft_realloc(file, sizeof(char *) * count, sizeof(char *) * (count + 1));
		if (!temp)
		{
			free(line);
			free_array(file);
			return (NULL);
		}
		file = temp;
		file[count] = line;
		count++;
	}
	temp = ft_realloc(file, sizeof(char *) * count, sizeof(char *) * (count + 1));
	if (!temp)
	{
		free_array(file);
		return (NULL);
	}
	file = temp;
	file[count] = NULL;
	return (file);
}

char	**read_file(char *filename)
{
	int	fd;
	char	**file;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\n");
		return(NULL); 
	}

	file = load_file_data(fd);
	close(fd);

	if (!file)
	{
		perror("Error\n");
		return (NULL);
	}
	return (file);
}
