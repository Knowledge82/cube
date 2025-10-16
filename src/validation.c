/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:45:08 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/10/09 14:05:05 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_map_symbol(char c)
{
	if (c !='0' && c != '1' && c !='N' &&
		c != 'S' && c !='E' && c !='W' && c != ' ')
		return (0);
	return (1);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if (!ft_iswhitespace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while(ft_iswhitespace(line[i]))
		i++;
	if (line[i] == '\0')
		return (0);
	while (line[i])
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
	while(file[i])
	{
		if (is_map_line(file[i]))
			return (i);
		i++;
	}
	return (-1);
}
