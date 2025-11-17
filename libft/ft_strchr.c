/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:08:29 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/17 17:21:56 by vdarsuye         ###   ########.fr       */
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
	if (let == '\0')
		return ((char *)s);
	return (NULL);
}
