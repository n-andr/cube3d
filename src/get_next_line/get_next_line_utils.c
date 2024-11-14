/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Natalia <Natalia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:49:50 by nandreev          #+#    #+#             */
/*   Updated: 2024/05/30 14:19:34 by Natalia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	length;

	length = 0;
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		str ++;
		length ++;
	}
	return (length);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (src == NULL)
		return (0);
	if (size > 0)
	{
		while (src[i] && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s_join;
	size_t	total_len;

	total_len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	s_join = malloc (total_len * sizeof(char));
	if (total_len == 0 || s_join == 0)
		return (NULL);
	ft_strlcpy(s_join, s1, ft_strlen((char *)s1) + 1);
	ft_strlcpy(s_join + ft_strlen((char *)s1), s2, ft_strlen((char *)s2) + 1);
	return (s_join);
}

char	*ft_strchr(const char *s, int c)
{
	char	*s1;
	char	ch;

	ch = (char)c;
	s1 = (char *)s;
	while (*s1 != '\0')
	{
		if (*s1 == ch)
			return (s1);
		s1++;
	}
	if (*s1 == ch)
		return (s1);
	return (NULL);
}
