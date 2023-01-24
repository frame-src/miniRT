/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:05:41 by frmessin          #+#    #+#             */
/*   Updated: 2023/01/23 18:38:53 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int		free_scene(t_scene *scene);
int		obj_counter(char *filename, int *spherecount,
			int *planecount, int *cylindercount);
void	*alloc_objects(t_scene *scene, int counters[3]);
t_scene	*alloc_scene(char *filename);

int	free_scene(t_scene *scene)
{
	if (scene)
	{
		ft_objsfree(scene->objects);
		free(scene);
	}
	return (0);
}

int	obj_counter(char *filename, int *spherecount,
	int *planecount, int *cylindercount)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "sp ", 3))
			*spherecount = *spherecount + 1;
		if (!ft_strncmp(line, "pl ", 3))
			*planecount = *planecount + 1;
		if (!ft_strncmp(line, "cy ", 3))
			*cylindercount = *cylindercount + 1;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

void	*alloc_objects(t_scene *scene, int counters[3])
{
	int			i;
	t_object	*tmp;

	i = -1;
	while (++i < counters[0] + counters[1] + counters[2])
	{
		tmp = ft_objnew();
		if (!tmp && ft_objsfree(scene->objects))
			return (NULL);
		ft_objadd_back(&scene->objects, tmp);
	}
	return ((void *)1);
}

/*sphere 0, plane 1, cylinder 2*/
t_scene	*alloc_scene(char *filename)
{
	int		fd;
	int		counters[3];
	t_scene	*scene;

	ft_memset(counters, 0, 3 * sizeof(int));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (obj_counter(filename, counters, counters + 1, counters + 2) == -1
		&& !close(fd))
		return (NULL);
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene && !close(fd))
		return (NULL);
	if (!alloc_objects(scene, counters) && !close(fd))
		return (NULL);
	close(fd);
	return (scene);
}
