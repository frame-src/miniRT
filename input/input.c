/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:56:36 by mawinter          #+#    #+#             */
/*   Updated: 2023/01/23 17:21:49 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	get_file(char *filename)
{
	int	flen;
	int	fd;

	fd = 0;
	flen = ft_strlen(filename);
	if (flen < 3 && write(2, "Error\nFilename too small\n", 26))
		return (-1);
	if (ft_strcmp(filename + flen - 3, ".rt")
		&& write(2, "Error\nFilename not ending with .rt\n", 36))
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0 && write(2, "Error\nCould not open file\n", 27))
		return (-1);
	return (fd);
}

int	inc(int *ptr)
{
	*ptr = *ptr + 1;
	return (1);
}

int	valid_line(char *line, int *ca, int *cc, int *cl)
{
	if (ft_strlen(line) == 1 && line[0] == '\n')
		;
	else if (!ft_strncmp(line, "A ", 2) && inc(ca))
		return (valid_ambient(line));
	else if (!ft_strncmp(line, "C ", 2) && inc(cc))
		return (valid_camera(line));
	else if (!ft_strncmp(line, "L ", 2) && inc(cl))
		return (valid_light(line));
	else if (!ft_strncmp(line, "sp ", 3))
		return (valid_sphere(line));
	else if (!ft_strncmp(line, "pl ", 3))
		return (valid_plane(line));
	else if (!ft_strncmp(line, "cy ", 3))
		return (valid_cylinder(line));
	else if (write(2, SPECIFIIER, 26))
		return (FALSE);
	return (TRUE);
}

int	valid_input(char *filename)
{
	int		fd;
	char	*line;
	int		counters[3];

	counters[0] = 0;
	counters[1] = 0;
	counters[2] = 0;
	fd = get_file(filename);
	if (fd == -1)
		return (FALSE);
	line = get_next_line(fd);
	while (line)
	{
		if (!valid_line(line, &counters[1], &counters[0], &counters[2])
			&& free_1(line) && !close(fd))
			return (FALSE);
		if ((counters[0] == 2 || counters[1] == 2 || counters[2] == 2)
			&& write(2, REPT, 63) && !close(fd))
			return (FALSE);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (TRUE);
}
