/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:13:17 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/08/13 16:41:23 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

static char	*ft_str_copy_cat(char *new_str, char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (s1[++i])
		new_str[i] = s1[i];
	j = -1;
	while (s2[++j])
		new_str[i + j] = s2[j];
	new_str[i + j] = '\0';
	return (new_str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_str;

	if (!s1)
	{
		s1 = (char *)malloc(1);
		if (!s1)
			return (NULL);
		*s1 = '\0';
	}
	if (!s2)
		return (s1);
	new_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		return (NULL);
	new_str = ft_str_copy_cat(new_str, s1, s2);
	free(s1);
	return (new_str);
}
