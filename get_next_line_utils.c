/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:19:22 by sbehar            #+#    #+#             */
/*   Updated: 2024/11/26 11:08:01 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	if (str == NULL)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*s3;
	char	*ptr;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s3 = malloc(len1 + len2 + 1);
	if (!s3)
		return (NULL);
	ptr = s3;
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (s3);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned int)c;
	while (*s)
	{
		if (*s == (char)uc)
			return ((char *)s);
		s++;
	}
	if (uc == '\0')
		return ((char *)s);
	return ((void *)0);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = 0;
	while (s[len])
		len++;
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return ((void *)0);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strndup(const char *s, size_t n)
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




