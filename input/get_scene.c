/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 19:43:16 by marius            #+#    #+#             */
/*   Updated: 2022/12/16 11:51:13 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

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
	printf("sphere counter: %d\n", counters[0]);
	printf("plane counter: %d\n", counters[1]);
	printf("cylinder counter: %d\n", counters[2]);
	if (!alloc_objects(scene, counters) && !close(fd))
		return (NULL);
	close(fd);
	return (scene);
}

int	free_scene(t_scene *scene)
{
	if (scene)
	{
		ft_objsfree(scene->objects);
		free(scene);
	}
	return (0);
}

t_color	get_color_field(char *field)
{
	char	**triple;
	int		i;
	t_color	c;

	i = 0;
	triple = ft_split(field, ',');
	if (!triple)
		return ((t_color){-1, -1, -1});
	while (triple[i])
	{
		if (!i)
			c.r = ft_atod(triple[i]);
		else if (i == 1)
			c.g = ft_atod(triple[i]);
		else
			c.b = ft_atod(triple[i]);
		i++;
	}
	free_split(triple);
	return (c);
}

t_vec3	get_vector_field(char *field)
{
	char	**triple;
	int		i;
	t_vec3	c;

	i = 0;
	triple = ft_split(field, ',');
	if (!triple)
		return ((t_vec3){INFINITY, INFINITY, INFINITY});
	while (triple[i])
	{
		if (i == 0)
			c.x = ft_atod(triple[i]);
		else if (i == 1)
			c.y = ft_atod(triple[i]);
		else
			c.z = ft_atod(triple[i]);
		i++;
	}
	free_split(triple);
	return (c);
}

int	load_ambient(char *line, t_ambient *ambient)
{
	char	**fields;

	fields = ft_split(line, ' ');
	if (!fields)
		return (0);
	ambient->ratio = ft_atod(fields[1]);
	ambient->color = get_color_field(fields[2]);
	if (ambient->color.r == -1.0L && free_split(fields))
		return (0);
	ambient->ratiocolor.r = ambient->color.r * ambient->ratio;
	ambient->ratiocolor.g = ambient->color.g * ambient->ratio;
	ambient->ratiocolor.b = ambient->color.b * ambient->ratio;
	free_split(fields);
	return (1);
}

int	set_cam_rays(int fov, t_vec3 rays[HEIGHT][WIDTH])
{
	int		x;
	int		y;
	t_vec3	ray;
	double	xstep;
	double	ystep;
	double	screenratio;

	screenratio = (double) WIDTH / (double) HEIGHT;
	y = 0;
	if (!fov)
		return (0);
	double width = screenratio * tan(M_PI / 180.0L * (fov / 2));
	if (fov == 180)
		width = 1000;
	xstep = width / WIDTH;
	ystep = 1.0L / HEIGHT;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray.x = - width / 2.0L + x * xstep + 0.5 * xstep;
			ray.y = 0.5 - y * ystep - 0.5 * ystep;
			ray.z = 1;
			vec3_normalize(&ray);
			rays[y][x] = ray;
			x++;
		}
		y++;
	}
	return (1);
}

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

int	load_light(char *line, t_light *light)
{
	char	**fields;

	fields = ft_split(line, ' ');
	if (!fields)
		return (0);
	light->position = get_vector_field(fields[1]);
	if (light->position.x == INFINITY && free_split(fields))
		return (0);
	light->brightness_ratio = ft_atod(fields[2]);
	free_split(fields);
	return (1);
}

int	load_sphere(char *line, t_object *object)
{
	char	**fields;

	object->type = 's';
	object->sphere = malloc(sizeof(t_sphere));
	if (!object->sphere)
		return (0);
	fields = ft_split(line, ' ');
	if (!fields && free_1(object->sphere))
		return (0);
	object->sphere->position = get_vector_field(fields[1]);
	if (object->sphere->position.x == INFINITY && free_split(fields))
		return (0);
	object->sphere->radius = ft_atod(fields[2]) / 2;
	object->sphere->color = get_color_field(fields[3]);
	if (object->sphere->color.r == -1 && free_split(fields))
		return (0);
	free_split(fields);
	return (1);
}

int	load_plane(char *line, t_object *obj)
{
	char	**fields;
	t_plane	*plane;

	obj->type = 'p';
	obj->plane = malloc(sizeof(t_plane));
	if (!obj->plane)
		return (0);
	plane = obj->plane;
	fields = ft_split(line, ' ');
	if (!fields && free_1(obj->plane))
		return (0);
	plane->position = get_vector_field(fields[1]);
	if (plane->position.x == INFINITY && free_split(fields))
		return (0);
	plane->normal_vec = get_vector_field(fields[2]);
	if (plane->position.x == INFINITY && free_split(fields))
		return (0);
	plane->color = get_color_field(fields[3]);
	if (plane->color.r == -1 && free_split(fields))
		return (0);
	if (!d_nearly_equal(1.0L, vec3_dot(plane->normal_vec, plane->normal_vec))
		&& free_split(fields)
		&& write(2, "Plane Orientation vector must be normalized\n", 45))
		return (0);
	return (free_split(fields));
}

void	load_cyl_help(t_cylinder *cyl, char **fields)
{
	cyl->diameter = ft_atod(fields[3]);
	cyl->height = ft_atod(fields[4]);
	cyl->color = get_color_field(fields[5]);
	cyl->m_to_world = object_to_world(cyl->orientation, cyl->position);
	invert_matrix(cyl->m_to_world.m, cyl->m_to_cylinder.m);
}

int	load_cylinder(char *line, t_object *object)
{
	char		**fields;
	t_cylinder	*cyl;

	object->type = 'c';
	object->cylinder = malloc(sizeof(t_cylinder));
	if (!object->cylinder)
		return (0);
	cyl = object->cylinder;
	fields = ft_split(line, ' ');
	if (!fields && free_1(object->cylinder))
		return (0);
	cyl->position = get_vector_field(fields[1]);
	if (cyl->position.x == INFINITY && free_split(fields))
		return (0);
	cyl->orientation = get_vector_field(fields[2]);
	if (cyl->position.x == INFINITY && free_split(fields))
		return (0);
	load_cyl_help(cyl, fields);
	if (cyl->color.r == -1 && free_split(fields))
		return (0);
	if (!d_nearly_equal(1.0L, vec3_dot(cyl->orientation, cyl->orientation))
		&& free_split(fields)
		&& write(2, "Cylinder Orientation vector must be normalized\n", 48))
		return (0);
	return (free_split(fields));
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
