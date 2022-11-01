/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:56:36 by mawinter          #+#    #+#             */
/*   Updated: 2022/10/31 20:06:27 by marius           ###   ########.fr       */
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
	int		one_cam;
	int		one_ambient;
	int		one_light;

	one_ambient = 0;
	one_light = 0;
	one_cam = 0;
	fd = get_file(filename);
	if (fd == -1)
		return (FALSE);
	line = get_next_line(fd);
	while (line)
	{
		if ((one_cam == 2 || one_ambient == 2 || one_light == 2)
			&& write(2, DECLAREDOUBLE, 63) && !close(fd))
			return (FALSE);
		if (!valid_line(line, &one_ambient, &one_cam, &one_light)
			&& free_1(line) && !close(fd))
			return (FALSE);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (TRUE);
}