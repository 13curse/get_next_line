/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 23:11:37 by sbehar            #+#    #+#             */
/*   Updated: 2024/11/26 23:11:37 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_until_newline(int fd, char buffer[BUFFER_SIZE + 1], char **saved)
{
	int		bytes_read;
	char	*newline_pos;

	while (1)
	{
		newline_pos = ft_strchr(*saved, '\n');
		if (newline_pos != NULL)
			break;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break;
		buffer[bytes_read] = '\0';
		*saved = ft_strjoin(*saved, buffer);
	}
	return (newline_pos);
}

static char	*extract_line(char **saved_line)
{
	char	**split_result;
	char	*after;

	split_result = ft_split(*saved_line, '\n');
	after = split_result[0];

	if (split_result[1] != NULL)
	{
		free(*saved_line);
		*saved_line = split_result[1];
	}
	else
	{
		free(*saved_line);
		*saved_line = NULL;
	}
	free(split_result);
	return (after);
}

char	*get_next_line(int fd)
{
	static char	*saved = NULL;
	char	buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_until_newline(fd, buffer, &saved) == NULL && saved == NULL)
		return NULL;
	return (extract_line(&saved));
}