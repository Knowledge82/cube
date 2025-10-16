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
	else if (line[i] == 'F' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
		id = ft_strdup("F");
	else if (line[i] == 'C' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
		id = ft_strdup("C");
	return (id);
}

int	parse_texture(char *line, t_config *config, char *id)
{
	char	*path_texture;

	if (strcmp(id, "NO") == 0)
	{
		if (config->north != NULL)
			return (error_msg("Dublicate value in map config"), 0);
		path_texture = ft_substr(line, )////////////////////////////////////////////
	}
}


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
