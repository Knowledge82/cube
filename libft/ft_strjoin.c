/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:13:04 by vdarsuye          #+#    #+#             */
/*   Updated: 2024/07/15 18:30:24 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest_str;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL)
		s1_len = 0;
	else
		s1_len = ft_strlen(s1);
	if (s2 == NULL)
		s2_len = 0;
	else
		s2_len = ft_strlen(s2);
	dest_str = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!dest_str)
		return (NULL);
	ft_memcpy(dest_str, s1, s1_len);
	ft_memcpy(dest_str + s1_len, s2, s2_len);
	dest_str[s1_len + s2_len] = '\0';
	return (dest_str);
}
