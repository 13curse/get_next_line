# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

int	main()
{
	int		fd;
	char	*line;

	fd = open("main.c", O_RDONLY);
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
