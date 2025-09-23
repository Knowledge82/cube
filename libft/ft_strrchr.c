/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:47:40 by vdarsuye          #+#    #+#             */
/*   Updated: 2024/07/13 20:08:56 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	let;
	char	*coincidencia;

	let = (unsigned char)c;
	coincidencia = NULL;
	while (*s)
	{
		if (*s == let)
			coincidencia = (char *)s;
		s++;
	}
	if (let == '\0')
		return ((char *)s);
	return (coincidencia);
}
