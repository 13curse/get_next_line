/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:54:52 by sbehar            #+#    #+#             */
/*   Updated: 2024/12/03 13:48:55 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n > 0)
	{
		*p = 0;
		p++;
		n--;
	}
}

static char	*read_and_join(int fd, char *buffer)
{
	char		line[BUFFER_SIZE + 1];
	ssize_t		status;
	char		*temp;

	if (!buffer)
		buffer = ft_strdup("");
	while (!ft_strchr(buffer, '\n'))
	{
		ft_bzero(line, BUFFER_SIZE + 1);
		status = read(fd, line, BUFFER_SIZE);
		if (status < 0)
		{
			free(buffer);
			return (NULL);
		}
		line[status] = '\0';
		if (status == 0)
			break ;
		temp = ft_strjoin(buffer, line);
		buffer = temp;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	saved[MAX_FD][BUFFER_SIZE + 1];
	char		*buffer;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_strdup(saved[fd]);
	ft_bzero(saved[fd], BUFFER_SIZE + 1);
	buffer = read_and_join(fd, buffer);
	if (!buffer)
		return (NULL);
	ft_split(&buffer, saved[fd]);
	if (ft_strlen(buffer) == 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

/* int	main()
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*line;

	fd1 = open("text1.txt", O_RDONLY);
	fd2 = open("text2.txt", O_RDONLY);
	fd3 = open("text3.txt", O_RDONLY);
	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
	{
		printf("Erreur d'ouverture du fichier\n");
		return (1);
	}
	printf("Lecture alternée des fichiers :\n");

	line = get_next_line(fd1);
	printf("fd1 (1er tour) : %s", line);
	free(line);
	line = get_next_line(fd2);
	printf("fd2 (1er tour) : %s", line);
	free(line);
	line = get_next_line(fd3);
	printf("fd3 (1er tour) : %s", line);
	free(line);
	line = get_next_line(fd1);
	printf("fd1 (2eme tour) : %s", line);
	free(line);
	line = get_next_line(fd2);
	printf("fd2 (2eme tour) : %s", line);
	free(line);
	line = get_next_line(fd3);
	printf("fd3 (2eme tour) : %s", line);
	free(line);
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
} */