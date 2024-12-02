/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:15:00 by sbehar            #+#    #+#             */
/*   Updated: 2024/12/02 14:07:58 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	if (str == (void *)0)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	char	*ptr;
	char	*s4;

	s4 = s1;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
		return (NULL);
	ptr = s3;
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	free(s4);
	return (s3);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strndup(char *s, size_t n)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	while (i < n && s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	ft_split(char **s, char *saved)
{
	int	i;
	int	j;
	int	a;

	i = 0;
	j = 0;
	while ((*s)[i] && (*s)[i] != '\n')
		i++;
	if ((*s)[i])
		i++;
	a = i;
	while ((*s)[a])
	{
		saved[j] = (*s)[a];
		a++;
		j++;
	}
	saved[j] = '\0';
	if ((*s)[i])
		(*s)[i] = '\0';
}
