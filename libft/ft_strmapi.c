/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:46:24 by vdarsuye          #+#    #+#             */
/*   Updated: 2024/07/20 13:21:00 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*dest;
	size_t			len;

	len = ft_strlen(s);
	if (!s || !f)
		return (NULL);
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	index = 0;
	while (s[index])
	{
		dest[index] = f(index, s[index]);
		index++;
	}
	dest[index] = '\0';
	return (dest);
}
