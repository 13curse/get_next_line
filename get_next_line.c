/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:19:25 by sbehar            #+#    #+#             */
/*   Updated: 2024/11/26 11:11:45 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_and_store(int fd, char *buffer)
{
	char	temp[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	while ((bytes_read = read(fd, temp, BUFFER_SIZE)) > 0)
	{
		temp[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, temp);
		if (ft_strchr(temp, '\n'))
			break;
	}
	return (buffer);
}

char	*extract_line(char **buffer)
{
	char	*line;
	char	*newline_pos;
	size_t	line_length;
	char	*new_buffer;

	newline_pos = ft_strchr(*buffer, '\n');
	if (newline_pos)
	{
		line_length = newline_pos - *buffer + 1;
		line = ft_strndup(*buffer, line_length);
		new_buffer = ft_strdup(newline_pos + 1);
		free(*buffer);
		*buffer = new_buffer;
	}
	else
	{
		line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_and_store(fd, buffer);
	if (!buffer || !*buffer)
		return (NULL);
	line = extract_line(&buffer);
	if (line)
	{
		free(buffer);
		buffer = NULL;
	}
	return (line);
}

int	main()
{
	int fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Erreur d'ouverture du fichier");
		return (1);
	}
	line = get_next_line(fd);
	if (line)
	{
		printf("Première ligne : %s\n", line);
		free(line);
	}
	else
		printf("Aucune ligne lue.\n");
	close(fd);
	return (0);
}
	
