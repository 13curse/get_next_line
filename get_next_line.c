/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:54:52 by sbehar            #+#    #+#             */
/*   Updated: 2024/11/28 16:30:11 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *s)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = 0;
	while (s[len])
		len++;
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// static char	*read_until_newline(int fd, char buffer[BUFFER_SIZE + 1], char **saved)
// {
// 	int		bytes_read;
// 	char	*newline_pos;
// 	char	*temp;

// 	while (1)
// 	{
// 		newline_pos = ft_strchr(*saved, '\n');
// 		if (newline_pos != NULL)
// 			break;
// 		bytes_read = read(fd, buffer, BUFFER_SIZE);
// 		if (bytes_read <= 0)
// 			break;
// 		buffer[bytes_read] = '\0';
// 		temp = ft_strjoin(*saved, buffer);
// 		if (!temp)
// 			return (NULL);
// 		free(*saved);
// 		*saved = temp;
// 	}
// 	return (newline_pos);
// }

// static char	*extract_line(char **saved_line)
// {
// 	char	**split_result;
// 	char	*after;

// 	split_result = ft_split(*saved_line, '\n');
// 	if (!split_result)
// 		return (NULL);
// 	after = split_result[0];
// 	// free(*saved_line);
// 	*saved_line = split_result[1];
// 	free(split_result);
// 	return (after);
// }

char	*get_next_line(int fd)
{
	static char	saved[BUFFER_SIZE + 1];
	char	*buffer;
	int status ;
	char	line[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0 || !(buffer = ft_strdup(saved)))
		return (NULL);
	// buffer = ft_strdup(saved);
	saved[0] = '\0';
	while (!ft_strchr(buffer, '\n'))
	{
		status = read(fd, line, BUFFER_SIZE);
		if (status < 0)
		{
			free(buffer);
			return(NULL);
		}
		if (status == 0)
			break;
		line[status] = '\0';
		buffer = ft_strjoin(buffer, line);
	}
	ft_split(&buffer, saved);
	if (ft_strlen(buffer) == 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

int	main()
{
	int		fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Erreur d'ouverture du fichier\n");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Ligne lue : %s",  line);
		free(line);
	}
	close(fd);
	return (0);
}