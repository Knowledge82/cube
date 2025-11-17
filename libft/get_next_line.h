/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarsuye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:19:32 by vdarsuye          #+#    #+#             */
/*   Updated: 2025/11/17 17:22:57 by vdarsuye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>  // для использования функции read()
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
// Функции, которые используются в get_next_line.c
char	*get_next_line(int fd);
char	*read_from_fd(int fd, char *stored);
char	*extract_line(char *stored);
char	*update_stored(char *stored);
/*
// Функции, которые используются в get_next_line_utils.c
size_t  ft_strlen(const char *str);
char    *ft_strjoin(char const *s1, char const *s2);
void    *ft_memcpy(void *dest, const void *src, size_t len);
char    *ft_strchr(const char *s, int c);
char    *ft_substr(char const *s, unsigned int start, size_t len);
*/
#endif
