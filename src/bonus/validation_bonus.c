/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 12:54:03 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/16 19:58:16 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_map_symbol(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E'
		&& c != 'W' && c != ' ' && c != 'X' && c != 'D')
		return (0);
	return (1);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_is_whitespace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (ft_is_whitespace(line[i]))
		i++;
	if (line[i] == '\0')
		return (0);
	while (line[i] && line[i] != '\n' && line[i] != '\r')
	{
		if (!is_map_symbol(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	find_map_start(char **file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (is_map_line(file[i]))
			return (i);
		i++;
	}
	return (-1);
}
