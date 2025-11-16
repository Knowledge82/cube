/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:19:10 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/12 13:19:11 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static char	*extract_path(char *line, char *id)
{
	char	*path;
	int		i;
	size_t	len;

	i = 0;
	while (ft_is_whitespace(line[i]))
		i++;
	i = i + ft_strlen(id);
	while (ft_is_whitespace(line[i]))
		i++;
	path = ft_strdup(line + i);
	if (!path)
		return (error_msg("Mem alloc failed"), NULL);
	len = ft_strlen(path);
	while ((len > 0) && ft_is_whitespace(path[len - 1]))
	{
		path[len - 1] = '\0';
		len--;
	}
	if (path[0] == '\0')
	{
		error_msg("Empty path");
		return (free(path), NULL);
	}
	return (path);
}

int	parse_texture(char *line, t_config *config, char *id)
{
	char	**field_ptr;

	field_ptr = NULL;
	if (ft_strcmp(id, "NO") == 0)
		field_ptr = &config->north;
	else if (ft_strcmp(id, "SO") == 0)
		field_ptr = &config->south;
	else if (ft_strcmp(id, "WE") == 0)
		field_ptr = &config->west;
	else if (ft_strcmp(id, "EA") == 0)
		field_ptr = &config->east;
	if (*field_ptr != NULL)
		return (error_msg("Duplicate texture identifier"), 0);
	*field_ptr = extract_path(line, id);
	if (!*field_ptr)
		return (0);
	return (1);
}
