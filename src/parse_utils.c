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

int	check_color_data_range(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
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
	if (!config->north || !config->south || !config->west || !config->east)
		return (error_msg("Missing texture(s)"), 0);
	//vse param - ok
	//file_exists and can be open
	//color != -1 and 0-255
	return 1;
}
