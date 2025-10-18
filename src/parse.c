#include "cube.h"

char	*get_identifier(char *line)
{
	char	*id;
	int		i;

	id = NULL;
	i = 0;
	while (ft_iswhitespace(line[i]))
		i++;
	if (ft_strncmp(&line[i], "NO", 2) == 0 && (ft_iswhitespace(line[i + 2]) || line[i + 2] == '\0'))
		id = ft_strdup("NO");
	else if (ft_strncmp(&line[i], "SO", 2) == 0 && (ft_iswhitespace(line[i + 2]) || line[i + 2] == '\0'))
		id = ft_strdup("SO");
	else if (ft_strncmp(&line[i], "WE", 2) == 0 && (ft_iswhitespace(line[i + 2]) || line[i + 2] == '\0'))
		id = ft_strdup("WE");
	else if (ft_strncmp(&line[i], "EA", 2) == 0 && (ft_iswhitespace(line[i + 2]) || line[i + 2] == '\0'))
		id = ft_strdup("EA");
	else if (line[i] == 'F' && (ft_iswhitespace(line[i + 1]) || line[i + 1] == '\0'))
		id = ft_strdup("F");
	else if (line[i] == 'C' && (ft_iswhitespace(line[i + 1]) || line[i + 1] == '\0'))
		id = ft_strdup("C");
	return (id);
}

char	*extract_path(char *line, char *id)
{
	char	*path;
	int		i;

	i = 0;
	while (ft_iswhitespace(line[i]))
		i++;
	i = i + ft_strlen(id);
	while (ft_iswhitespace(line[i]))
		i++;
	path = ft_strdup(line + i);
	if (!path)
		return (error_msg("Mem alloc failed"), NULL);
	if (path[0] == '\0')
	{
		error_msg("Empty path");
		return (free(path), NULL);
	}
	return (path);
}

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
		return ("Path error", 0);
	return (1);
}

int	parse_number(char *line, int *i) // need protect from overflow
{
	int	num;
	int	digit_count;

	num = 0;
	digit_count = 0;
	while (ft_iswhitespace(line[*i]))
		(*i)++;
	while(ft_isdigit(line[*i]))
	{
		num = num * 10 + (line[*i] - '0');
		(*i)++;
		digit_count++;
	}
	if (digit_count == 0)
		return (-1);
	return (num);
}

int	check_color_data_range(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return 0;
	return (1);
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
			return (error_msg("Wrong color data"), 0);
	i++;
	g = parse_number(line, &i);
	if (line[i] != ',')
			return (error_msg("Wrong color data"), 0);
	i++;
	b = parse_number(line, &i);
	if (!check_color_data_range(r, g ,b))
			return (error_msg("Wrong color data"), 0);
	field = NULL;
	if (ft_strcmp(id, "F") == 0)
		field = &config->floor_color;
	else
		field = &config->ceiling_color;
	return (1);

}

int	file_exist(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	validate_config(t_config *config)
{
	if ()
	//vse param - ok
	//file_exists and can be open
	//color != -1 and 0-255
	return 1;
}

//char	*parse_identifier(char *line, t_config *config) - skoree vsego

int	parse_config(char **file, int map_start, t_config *config)
{
	char	*id;
	int		i;

	i = 0;
	while (i < map_start)
	{
		if (is_empty_line(file[i]))
		{
			i++;
			continue;
		}
		id = get_identifier(file[i]);
		if (id == "F" || id == "C")
			parse_color(file[i], config, id);
		else
			parse_texture(file[i], config, id);

		i++;
	}
	validate_config(config);
}


