/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:19:59 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/17 17:20:01 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
size_t  ft_strlen(const char *str)
{
        size_t  len;

        len = 0;
        while (str[len] != '\0')
                len++;
        return (len);
}

void    *ft_memcpy(void *dest, const void *src, size_t len)
{
        unsigned char           *d;
        const unsigned char     *s;

        d = (unsigned char *)dest;
        s = (const unsigned char *)src;
        if (!dest && !src)
                return (NULL);
        while (len)
        {
                *d = *s;
                d++;
                s++;
                len--;
        }
        return (dest);
}
char    *ft_strjoin(char const *s1, char const *s2)
{
        char    *dest_str;
        size_t  s1_len;
        size_t  s2_len;

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
char    *ft_strchr(const char *s, int c)
{
        char    let;

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
char    *ft_substr(char const *s, unsigned int start, size_t len)
{
        size_t  i;
        size_t  s_len;
        size_t  max_len;
        char    *substr;

        if (!s)
                return (NULL);
        s_len = ft_strlen(s);
        if (start >= s_len)
                return (NULL);
        max_len = s_len - start;
        if (len > max_len)
                len = max_len;
        substr = (char *)malloc((len + 1) * sizeof(char));
        if (!substr)
                return (NULL);
        i = 0;
        while (i < len)
        {
                substr[i] = s[start + i];
                i++;
        }
        substr[i] = '\0';
        return (substr);
}*/
