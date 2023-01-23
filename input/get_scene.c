/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 19:43:16 by marius            #+#    #+#             */
/*   Updated: 2023/01/23 12:05:25 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	load_camera(char *line, t_camera *camera)
{
	char	**fields;

	fields = ft_split(line, ' ');
	if (!fields)
		return (0);
	camera->position = get_vector_field(fields[1]);
	if (camera->position.x == INFINITY && free_split(fields))
		return (0);
	camera->direction = get_vector_field(fields[2]);
	if (camera->direction.x == INFINITY && free_split(fields))
		return (0);
	camera->fov = ft_atod(fields[3]);
	set_cam_rays(camera->fov, camera->rays);
	camera->m_camera_world = object_to_world(camera->direction,
			camera->position);
	invert_matrix(camera->m_camera_world.m, camera->m_world_camera.m);
	if (!d_nearly_equal(1.0L, vec3_dot(camera->direction, camera->direction))
		&& free_split(fields)
		&& write(2, "Camera Orientation vector must be normalized\n", 46))
		return (0);
	free_split(fields);
	return (1);
}

char	*get_scene_loop_inner(char **line, t_scene *scene, int *idx)
{
	if (!ft_strncmp(line[0], "A ", 2)
		&& !load_ambient(line[0], &scene->ambient_l)
		&& free_1(line[0]))
		return (NULL);
	else if (!ft_strncmp(line[0], "C ", 2)
		&& !load_camera(line[0], &scene->camera)
		&& free_1(line[0]))
		return (NULL);
	else if (!ft_strncmp(line[0], "L ", 2)
		&& !load_light(line[0], &scene->light)
		&& free_1(line[0]))
		return (NULL);
	else if (!ft_strncmp(line[0], "sp ", 3)
		&& !load_sphere(line[0], ft_objat(scene->objects, (*idx)++)))
		return (NULL);
	else if (!ft_strncmp(line[0], "pl ", 3)
		&& !load_plane(line[0], ft_objat(scene->objects, (*idx)++)))
		return (NULL);
	else if (!ft_strncmp(line[0], "cy ", 3)
		&& !load_cylinder(line[0], ft_objat(scene->objects, (*idx)++)))
		return (NULL);
	return ((char *)1);
}

char	*get_scene_loop(char **line, t_scene *scene, int fd, int *idx)
{
	if (line[0][ft_strlen(line[0]) - 1] == '\n')
		line[0][ft_strlen(line[0]) - 1] = '\0';
	if (!get_scene_loop_inner(line, scene, idx))
	{
		close(fd);
		return (NULL);
	}
	free(line[0]);
	line[0] = get_next_line(fd);
	return ((char *)1);
}

/*sphere 0, plane 1, cylinder 2*/
t_scene	*get_scene(char *filename)
{
	int		fd;
	t_scene	*scene;
	char	*line;
	int		idx;

	idx = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	scene = alloc_scene(filename);
	if (!scene && !free_scene(scene))
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (!get_scene_loop(&line, scene, fd, &idx) && !free_scene(scene))
			return (NULL);
	}
	return (scene);
}
