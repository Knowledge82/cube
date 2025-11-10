/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:59:39 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/10 18:10:43 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static char	**handle_allocation_error(char *line, char **file)
{
	if (line)
		free(line);
	if (file)
		ft_free_array(file);
	return (NULL);
}

static char	**read_lines(int fd, int *count)
{
	char	**file;
	char	**temp;
	char	*line;

	file = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		temp = ft_realloc(file, sizeof(char *) * (*count),
				sizeof(char *) * ((*count) + 1));
		if (!temp)
			return (handle_allocation_error(line, file));
		file = temp;
		file[*count] = line;
		(*count)++;
		line = get_next_line(fd);
	}
	return (file);
}

static char	**load_lines_array(int fd)
{
	int		count;
	char	**file;
	char	**temp;

	count = 0;
	file = read_lines(fd, &count);
	if (!file)
		return (NULL);
	temp = ft_realloc(file, sizeof(char *) * count,
			sizeof(char *) * (count + 1));
	if (!temp)
		return (handle_allocation_error(NULL, file));
	file = temp;
	file[count] = NULL;
	return (file);
}

char	**read_file(const char *filename)
{
	int		fd;
	char	**file;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\n");
		return (NULL);
	}
	file = load_lines_array(fd);
	close(fd);
	if (!file)
	{
		perror("Error\n");
		return (NULL);
	}
	return (file);
}
