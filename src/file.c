/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:59:39 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/10/09 11:40:59 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static char	**load_file_data(int fd)
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
			ft_free_array(file);
			return (NULL);
		}
		file = temp;
		file[count] = line;
		count++;
	}
	temp = ft_realloc(file, sizeof(char *) * count, sizeof(char *) * (count + 1));
	if (!temp)
		return (ft_free_array(file), NULL);
	file = temp;
	file[count] = NULL;
	return (file);
}

char	**read_file(const char *filename)
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
