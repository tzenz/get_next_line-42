#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

# define BUFF_SIZE 1024

void	ft_bzero(void *s, size_t n)
{
		unsigned char *st;

			st = (unsigned char *)s;
				while (n--)
							*st++ = '\0';
}

void	*ft_memalloc(size_t size)
{
		void *st;

			if ((st = malloc(size)))
						ft_bzero(st, size);
				return (st);
}

int		get_next_line(const int fd, char **line)
{
	static char		s[1000];
	static char		buf[BUFF_SIZE];
	static int		i;
	static int		j;
	static int		l;

	i = 0;
	if (!s[i])
	{
		while ((i = read(fd, buf, BUFF_SIZE)))
		{
			if (i < 0)
				return (i);
			while (buf[i])
				s[j++] = buf[i++];
			i = 0;
		}
		s[j] = '\0';
	}
	printf ("j - %d, l - %d\n", j, l);
	if (s[l + 1] == '\0')
		return (0);
	*line = (char *)ft_memalloc(sizeof(j) + 1);
	while (s[l] != '\n' && s[l] != EOF && s[l] != '\0')
		line[0][i++] = s[l++];
	free(*line);
	line[0][i] = '\0';
	l++;
	return (1);
}

int				main(void)
{
	char		*line;
	int			fd;
	int			ret;
	int			count_lines;
	char		*filename;
	int			errors;

	filename = "gnl7_2.txt";
	fd = open(filename, O_RDONLY);
	if (fd > 2)
	{
		count_lines = 0;
		errors = 0;
		line = NULL;
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			if (count_lines == 0 && printf ("c1 - %d\n", strcmp(line, "1234567")) != 0)
			{
				printf("%s\n", line);	
				errors++;
			}
			if (count_lines == 1 && printf ("c2 - %d\n", strcmp(line, "abcdefgh")) != 0)
			{
				printf("%s\n", line);	
				errors++;
			}
			count_lines++;
			if (count_lines > 50)
				break ;
		}
		close(fd);
		if (count_lines != 2)
			printf("-> must have returned '1' twice instead of %d time(s)\n", count_lines);
		if (errors > 0)
			printf("-> must have read \"1234567\" and \"abcdefgh\"\n");
		if (count_lines == 2 && errors == 0)
			printf("OK\n");
	}
	else
		printf("An error occured while opening file %s\n", filename);
	return (0);
}
