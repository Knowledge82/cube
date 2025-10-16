/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:01:34 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/10/08 16:27:58 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	error_msg(char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd('\n', STDERR_FILENO);
}

int     check_extension(const char *filename)
{
        int     len;

	if (!filename)
		return (0);
        len = ft_strlen(filename);
        if (len < 4)
	       return 0;
	if (ft_strncmp(filename + len - 4, ".cub", 4) == 0)
                return (1);
	return (0);
}

