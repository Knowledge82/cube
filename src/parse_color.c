/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:20:04 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/12 13:20:05 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	parse_number(char *line, int *i)
{
	int	num;
	int	digit_count;

	num = 0;
	digit_count = 0;
	while (ft_is_whitespace(line[*i]))
		(*i)++;
	while (ft_isdigit(line[*i]))
	{
		if (digit_count >= 3)
			return (-1);
		num = num * 10 + (line[*i] - '0');
		(*i)++;
		digit_count++;
	}
	if (digit_count == 0)
		return (-1);
	return (num);
}

static uint32_t	parse_rgb(char *line, int *i)
{
	int	r;
	int	g;
	int	b;

	r = parse_number(line, i);
	if (r < 0)
		return (0xFFFFFFFF);
	if (line[*i] != ',')
		return (error_msg("Wrong color format"), 0xFFFFFFFF);
	(*i)++;
	g = parse_number(line, i);
	if (g < 0)
		return (0xFFFFFFFF);
	if (line[*i] != ',')
		return (error_msg("Wrong color format"), 0xFFFFFFFF);
	(*i)++;
	b = parse_number(line, i);
	if (b < 0)
		return (0xFFFFFFFF);
	if (!check_color_data_range(r, g, b))
		return (error_msg("Wrong color data range"), 0xFFFFFFFF);
	return ((r << 16) | (g << 8) | b);
}

int	parse_color(char *line, t_config *config, char *id)
{
	uint32_t	*field_ptr;
	uint32_t	color;
	int			i;

	i = 0;
	while (ft_is_whitespace(line[i]))
		i++;
	i = i + ft_strlen(id);
	while (ft_is_whitespace(line[i]))
		i++;
	color = parse_rgb(line, &i);
	if (color == 0xFFFFFFFF)
		return (0);
	field_ptr = NULL;
	if (ft_strcmp(id, "F") == 0)
		field_ptr = &config->floor_color;
	else
		field_ptr = &config->ceiling_color;
	if (*field_ptr != 0xFFFFFFFF)
		return (error_msg("Duplicate color data"), 0);
	*field_ptr = color;
	return (1);
}
