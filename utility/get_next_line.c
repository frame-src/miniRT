/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:12:58 by mawinter          #+#    #+#             */
/*   Updated: 2022/06/30 10:24:11 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include "get_next_line_utils.c"

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE];
	static char	infobuf[20 + BUFFER_SIZE];
	char		*line;
	int			linelen;

	if (setup(&linelen, fd, &line))
		return (NULL);
	if (get_idx_read(infobuf, 0) == 0)
		readnew(infobuf, buf, fd);
	while (0 < get_idx_read(infobuf, -1))
	{
		while (get_idx_read(infobuf, 0) < get_idx_read(infobuf, -1))
		{					
			line = join_line(infobuf, line, &linelen);
			if (!line)
				return (NULL);
			if (line[linelen - 1] == '\n')
				return (line);
		}
		readnew(infobuf, buf, fd);
	}
	return (line);
}

// # include "main.c"