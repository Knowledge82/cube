/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:56:06 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/10 15:26:56 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void    free_config(t_config *config)
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
}

void	cleanup(t_game *game)
{
	free_textures(&game->textures);
	if (game->map.grid)
		free_grid(game->map.grid);
	free_config(&game->config);
	if (game->mlx)
		mlx_terminate(game->mlx);
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

