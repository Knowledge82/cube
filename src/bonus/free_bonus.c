/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:22:54 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/15 16:24:14 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	free_config(t_config *config)
{
	if (config->north)
	{
		free(config->north);
		config->north = NULL;
	}
	if (config->south)
	{
		free(config->south);
		config->south = NULL;
	}
	if (config->west)
	{
		free(config->west);
		config->west = NULL;
	}
	if (config->east)
	{
		free(config->east);
		config->east = NULL;
	}
	if (config->door)
	{
		free(config->door);
		config->door = NULL;
	}
}

void	free_visited(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

void	free_queue(t_queue *queue)
{
	if (!queue)
		return ;
	free(queue->data);
	free(queue);
}

void	free_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

void	free_textures(t_textures *textures)
{
	if (textures->north != NULL)
	{
		mlx_delete_texture(textures->north);
		textures->north = NULL;
	}
	if (textures->south != NULL)
	{
		mlx_delete_texture(textures->south);
		textures->south = NULL;
	}
	if (textures->west != NULL)
	{
		mlx_delete_texture(textures->west);
		textures->west = NULL;
	}
	if (textures->east != NULL)
	{
		mlx_delete_texture(textures->east);
		textures->east = NULL;
	}
	if (textures->door != NULL)
	{
		mlx_delete_texture(textures->door);
		textures->door = NULL;
	}
}
