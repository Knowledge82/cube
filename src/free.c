/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:56:06 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/10/27 18:03:55 by vdarsuye         ###   ########.fr       */
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

