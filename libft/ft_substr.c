/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:58:51 by vdarsuye          #+#    #+#             */
/*   Updated: 2024/07/15 18:34:25 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	size_t	max_len;
	char	*substr;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	max_len = s_len - start;
	i = 0;
	if (start >= s_len)
		return (ft_calloc(1, sizeof(char)));
	if (len > max_len)
		len = max_len;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
