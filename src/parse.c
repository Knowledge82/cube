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
/*
if (path_texture[0] == '\0')
{
	free(path_texture);
	return (error_msg("Empty texture path"), 0);
}
   */

int	parse_config(char **file, int map_start, t_config *config)
{
	int	i;

	i = 0;
	while (i < map_start)
	{
		if (is_empty_line(file[i]))
		{
			i++;
			continue;
		}
		if ()
		i++;
	}
}


//validate_config
