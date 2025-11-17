/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:20:16 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/17 17:28:34 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*read_buffer(int fd)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	return (buffer);
}

char	*store_buffer(int fd, char *stored)
{
	char	*buffer;
	char	*temp;

	while (!stored || !ft_strchr(stored, '\n'))
	{
		buffer = read_buffer(fd);
		if (!buffer)
			return (stored);
		temp = ft_strjoin(stored, buffer);
		free(stored);
		free(buffer);
		stored = temp;
		if (!stored)
			return (NULL);
	}
	return (stored);
}

char	*extract_line(char *stored)
{
	int		i;
	char	*line;

	if (!stored || !stored[0])
		return (NULL);
	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (stored[i] == '\n')
		line = ft_substr(stored, 0, i + 1);
	else
		line = ft_substr(stored, 0, i);
	return (line);
}

char	*update_stored(char *stored)
{
	char	*new_stored;
	int		i;

	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (!stored[i])
	{
		free(stored);
		return (NULL);
	}
	new_stored = ft_substr(stored, i + 1, ft_strlen(stored) - i - 1);
	free(stored);
	return (new_stored);
}

char	*get_next_line(int fd)
{
	static char	*stored;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stored = store_buffer(fd, stored);
	if (!stored)
		return (NULL);
	line = extract_line(stored);
	stored = update_stored(stored);
	return (line);
}
