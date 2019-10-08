#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"

# define BUFF_SIZE 20

char	*ch(char *res, char **line)
{
	char	*tmp;

	if (res)
	{
		if ((tmp = ft_strchr(res, '\n')))
		{
			*tmp = '\0';
			*line = ft_strdup(res);
			ft_strcpy(res, ++tmp);
		}
		else
			*line = ft_strdup(res);
	}
	else
		*line = ft_strnew(1);
	return (tmp);
}

int		get_next_line(const int fd, char **line)
{
	static char		*res;
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	int				r;

	tmp = ch(res, line);
	while (!tmp && (r = read(fd, buf, BUFF_SIZE)))
	{
		buf[r] = '\0';
		if ((tmp = ft_strchr(buf, '\n')))
		{
			*tmp = '\0';
			res = ft_strdup(++tmp);
		}
		*line = ft_strjoin(*line, buf);
	}
	return (r || ft_strlen(res) || ft_strlen(*line)) ? 1 : 0;
}

int				main(void)
{
	char		*line;
	int			fd;
	int			ret;
	int			count_lines;
	char		*filename;
	int			errors;

	filename = "gnl1_3.txt";
	fd = open(filename, O_RDONLY);
	if (fd > 2)
	{
		count_lines = 0;
		errors = 0;
		line = NULL;
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			if (count_lines == 0 && strcmp(line, "1234567") != 0)
			{
				errors++;
			}
			if (count_lines == 1 && strcmp(line, "abcdefg") != 0)
			{
				printf("%s\n", line);				
				errors++;
			}
			if (count_lines == 2 && strcmp(line, "4567890") != 0)
			{	
				printf ("%s\n", line);			
				errors++;
			}
			if (count_lines == 3 && strcmp(line, "defghij") != 0)
			{
				printf ("%s\n", line);
				errors++;
			}
			count_lines++;
			if (count_lines > 50)
				break;
		}
		close(fd);
		if (count_lines != 4)
			printf("-> must have returned '1' four times instead of %d time(s)\n", count_lines);
		if (errors > 0)
		{
			printf("errors - %d\n", errors);
			printf("-> must have read \"1234567\", \"abcdefg\", \"4567890\" and \"defghij\"\n");
		}
		if (count_lines == 4 && errors == 0)
			printf("OK\n");
	}
	else
	printf("An error occured while opening file %s\n", filename);
	return (0);
}
