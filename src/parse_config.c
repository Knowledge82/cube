/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:18:23 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/12 13:18:25 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	parse_identifier(char *line, t_config *config)
{
	int		result;
	char	*id;

	id = get_identifier(line);
	if (!id)
		return (error_msg("Parse map config failed. Invalid identifier."), 0);
	if (ft_strcmp(id, "F") == 0 || ft_strcmp(id, "C") == 0)
		result = parse_color(line, config, id);
	else
		result = parse_texture(line, config, id);
	free(id);
	return (result);
}

int	parse_config(char **file, int map_start, t_config *config)
{
	int		i;

	i = 0;
	while (i < map_start)
	{
		if (is_empty_line(file[i]))
		{
			i++;
			continue ;
		}
		if (!parse_identifier(file[i], config))
			return (0);
		i++;
	}
	if (!validate_config(config))
		return (0);
	return (1);
}
