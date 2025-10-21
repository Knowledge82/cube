#include "cube.h"

int	parse_texture(char *line, t_config *config, char *id)
{
	char	**field;

	field = NULL;
	if (ft_strcmp(id, "NO") == 0)
		field = &config->north;
	else if (ft_strcmp(id, "SO") == 0)
		field = &config->south;
	else if (ft_strcmp(id, "WE") == 0)
		field = &config->west;
	else if (ft_strcmp(id, "EA") == 0)
		field = &config->east;
	if (*field != NULL)
		return (error_msg("Duplicate"), 0);
	*field = extract_path(line, id);
	if (!*field)
		return (error_msg("Path error"), 0);
	return (1);
}

int	parse_number(char *line, int *i)
{
	int	num;
	int	digit_count;

	num = 0;
	digit_count = 0;
	while (ft_iswhitespace(line[*i]))
		(*i)++;
	while(ft_isdigit(line[*i]))
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

int	parse_color(char *line, t_config *config, char *id)
{
	int *field;
	int	color;
	int	i;
	int	r, g, b;

	i = 0;
	while (ft_iswhitespace(line[i]))
		i++;
	i = i + ft_strlen(id);
	while (ft_iswhitespace(line[i]))
		i++;
	r = parse_number(line, &i);
	if (line[i] != ',')
			return (error_msg("Wrong color format"), 0);
	i++;
	g = parse_number(line, &i);
	if (line[i] != ',')
			return (error_msg("Wrong color format"), 0);
	i++;
	b = parse_number(line, &i);
	if (!check_color_data_range(r, g ,b))
			return (error_msg("Wrong color data range"), 0);
	field = NULL;
	if (ft_strcmp(id, "F") == 0)
		field = &config->floor_color;
	else
		field = &config->ceiling_color;
	if (*field == -1)
		return (error_msg("Duplicate color data"), 0);
	// convert to 0xRRGGBB for MLX
	color = (r << 16) | (g << 8) | b;
	*field = color;
	return (1);

}

int	parse_identifier(char *line, t_config *config)
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
			continue;
		}
		if (!parse_identifier(file[i], config))
			return (error_msg("Parse map config failed"), 0);
		i++;
	}
	if (!validate_config(config))
		return (0);
	return (1);
}
