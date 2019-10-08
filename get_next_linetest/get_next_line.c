/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 10:36:28 by tzenz             #+#    #+#             */
/*   Updated: 2019/10/08 14:18:06 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ch(char *res, char **line)
{
	char	*tmp;

	tmp = NULL;
	if (res)
		if ((tmp = ft_strchr(res, '\n')))
		{
			*tmp = '\0';
			*line = ft_strdup(res);
			ft_strcpy(res, ++tmp);
		}
		else
		{
			*line = ft_strdup(res);
			while (*res)
			{
				*res = '\0';
				res++;
			}
		}
	else
		*line = ft_strnew(1);
	return (tmp);
}

int		ch_lk(char *leak, char **line)
{
	int		i;

	i = 0;
	if (leak == 0 || *line == 0)
		return (0);
	if (leak)
		i = ft_strcmp(leak, *line);
	return (i);
}

int		get_next_line(const int fd, char **line)
{
	static char		*res;
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	char			*leak;
	int				r;

	if (line == 0)
		return (-1);
	if (ch_lk(leak, line) == 0)
	{
	tmp = ch(res, line);
	while (!tmp && (r = read(fd, buf, BUFF_SIZE)))
	{
		if (r < 0)
			return (-1);
		buf[r] = '\0';
		if ((tmp = ft_strchr(buf, '\n')))
		{
			*tmp = '\0';
			res = ft_strdup(++tmp);
		}
		leak = *line;
		*line = ft_strjoin(*line, buf);
	}
	}
//	return (r || ft_strlen(res) || ft_strlen(*line)) ? 1 : 0;
	return (1);
}

int		main(void)
{
	int		op1;
	int		op2;
	char	*ln;
	int		i = 5;

	op1 = open("file1", O_RDONLY);
	op2 = open("file2", O_RDONLY);
	while (i--)
	{
		get_next_line(op1, &ln);
		printf("%s\n", ln);
		get_next_line(op2, &ln);
		printf("%s\n", ln);
	}
	return (0);
}
