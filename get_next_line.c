/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:54:52 by sbehar            #+#    #+#             */
/*   Updated: 2024/11/30 18:55:52 by sbehar           ###   ########.fr       */
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
	while (1)
	{
		ft_bzero(line, BUFFER_SIZE + 1);
		status = read(fd, line, BUFFER_SIZE);
		if (status < 0)
		{
			free(buffer);
			return (NULL);
		}
		if (status == 0)
			break ;
		temp = ft_strjoin(buffer, line);
		//free(buffer);
		buffer = temp;
		//if (!buffer)
		//return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	saved[BUFFER_SIZE + 1];
	char		*buffer;
	//int			status;
	//char		line[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_strdup(saved);
	ft_bzero(saved, BUFFER_SIZE + 1);
	//saved[0] = '\0';
	/*while (!ft_strchr(buffer, '\n'))
	{
		status = read(fd, line, BUFFER_SIZE);
		if (status < 0)
		{
			free(buffer);
			return (NULL);
		}
		if (status == 0)
			break ;
		line[status] = '\0';
		buffer = ft_strjoin(buffer, line);
	}*/
	buffer = read_and_join(fd, buffer);
	if (!buffer)
		return (NULL);
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