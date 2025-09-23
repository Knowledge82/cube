/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:14:54 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/06/07 17:54:50 by pdoltu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_separator(char c, char separ)
{
	return (c == separ);
}

static int	words_count(const char *str, char separ)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_separator(str[i], separ))
			i++;
		if (str[i])
			count++;
		while (str[i] && !is_separator(str[i], separ))
			i++;
	}
	return (count);
}

static char	*extract_word(const char *str, int start, int len)
{
	char	*word;

	if (len <= 0)
		return (NULL);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strncpy(word, &str[start], len);
	return (word);
}

static char	**ft_split_utils(char **out, const char *str, char separ)
{
	int		i;
	int		j;
	int		start_word;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && is_separator(str[i], separ))
			i++;
		start_word = i;
		while (str[i] && !is_separator(str[i], separ))
			i++;
		if (i - start_word > 0)
		{
			out[j++] = extract_word(str, start_word, i - start_word);
			if (!out[j - 1])
				return (NULL);
		}
	}
	out[j] = NULL;
	return (out);
}

char	**ft_split(const char *str, char separ)
{
	char	**out;

	if (!str)
		return (NULL);
	out = (char **)malloc(sizeof(char *) * (words_count(str, separ) + 1));
	if (!out)
		return (NULL);
	out = ft_split_utils(out, str, separ);
	return (out);
}
