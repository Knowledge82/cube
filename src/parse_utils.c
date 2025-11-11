/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:49:01 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/06 13:56:49 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	is_valid_delim(char *line, int pos)
{
	if (ft_is_whitespace(line[pos]) || line[pos] == '\0')
		return (1);
	else
		return (0);
}

char	*get_identifier(char *line)
{
	char	*id;
	int		i;

	id = NULL;
	i = 0;
	while (ft_is_whitespace(line[i]))
		i++;
	if (ft_strncmp(&line[i], "NO", 2) == 0 && is_valid_delim(line, i + 2))
		id = ft_strdup("NO");
	else if (ft_strncmp(&line[i], "SO", 2) == 0 && is_valid_delim(line, i + 2))
		id = ft_strdup("SO");
	else if (ft_strncmp(&line[i], "WE", 2) == 0 && is_valid_delim(line, i + 2))
		id = ft_strdup("WE");
	else if (ft_strncmp(&line[i], "EA", 2) == 0 && is_valid_delim(line, i + 2))
		id = ft_strdup("EA");
	else if (line[i] == 'F' && is_valid_delim(line, i + 1))
		id = ft_strdup("F");
	else if (line[i] == 'C' && is_valid_delim(line, i + 1))
		id = ft_strdup("C");
	return (id);
}

int	check_color_data_range(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	return (1);
}

bool	file_exist(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		error_msg("Texture file not found");
		return (false);
	}
	close(fd);
	return (true);
}

int	validate_config(t_config *config)
{
	if (!config->north || !config->south || !config->west || !config->east)
		return (error_msg("Missing texture(s)"), 0);
	if (!file_exist(config->north) || !file_exist(config->south)
		|| !file_exist(config->west) || !file_exist(config->east))
		return (0);
	if (config->floor_color == 0xFFFFFFFF
		|| config->ceiling_color == 0xFFFFFFFF)
		return (error_msg("Missing color(s)"), 0);
	return (1);
}
