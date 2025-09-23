/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:08:29 by vdarsuye          #+#    #+#             */
/*   Updated: 2024/07/13 19:57:18 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	let;

	let = (unsigned char)c;
	while (*s)
	{
		if (*s == let)
			return ((char *)s);
		s++;
	}
	if (*s == let)
		return ((char *)s);
	return (NULL);
}
