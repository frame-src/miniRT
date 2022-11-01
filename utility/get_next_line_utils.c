/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:13:02 by mawinter          #+#    #+#             */
/*   Updated: 2022/10/31 15:29:41 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	readnew(char *infobufd, char *buf, int fd)
{
	int	res;
	int	readd;
	int	i;

	i = 0;
	readd = read(fd, buf, BUFFER_SIZE);
	res = readd;
	while (i < 20)
		infobufd[i++] = 0;
	i = 0;
	while (readd)
	{
		infobufd[19 - i++] = (readd % 10) + 48;
		readd = readd / 10;
	}
	i = -1;
	while (++i < res)
		infobufd[i + 20] = buf[i];
	return (1);
}

int	get_idx_read(char *infobufd, int mode)
{
	int	res;
	int	i;
	int	readd;

	i = 0;
	res = 0;
	readd = 0;
	if (mode == -1)
		readd = 10;
	if (mode == 0 || mode == -1)
	{
		while (infobufd[i + readd] == 0 && i < 10)
			i++;
		while (i < 10)
			res = res * 10 + (infobufd[readd + i++] - '0');
	}
	return (res);
}

int	setup(int *linelen, int fd, char **line)
{
	*linelen = 0;
	*line = NULL;
	if (read(fd, NULL, 0) < 0 || BUFFER_SIZE < 1)
		return (1);
	return (0);
}

char	*ft_bufjoin(char *line, int bufidx, char *buf, int linelen)
{
	char	*newstring;
	int		i;

	i = -1;
	newstring = (malloc((linelen + 2) * sizeof(char)));
	if (!newstring || (!line && linelen != 0) || !buf)
		return (NULL);
	while (++i < linelen && line)
		newstring[i] = line[i];
	newstring[i] = buf[bufidx];
	newstring[i + 1] = '\0';
	free(line);
	return (newstring);
}

char	*join_line(char *infobufd, char *line, int *linelen)
{
	int	oldbufidx;
	int	idx;

	idx = 0;
	oldbufidx = get_idx_read(infobufd, 0);
	line = ft_bufjoin(line, oldbufidx + 20, infobufd, *linelen);
	oldbufidx++;
	while (idx < 10)
	{
		infobufd[9 - idx++] = (oldbufidx % 10) + 48;
		oldbufidx = oldbufidx / 10;
	}
	(*linelen)++;
	return (line);
}
