/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 19:43:16 by marius            #+#    #+#             */
/*   Updated: 2022/11/28 18:38:50 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	obj_counter(char *filename, int *spherecount, int *planecount, int *cylindercount)
{
	int	fd;
	char *line;

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

void *alloc_objects(t_scene *scene, int counters[3])
{
	int i;
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
t_scene *alloc_scene(char *filename)
{
	int	fd;
	int	counters[3];
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
	char **triple;
	int		i;
	t_color	c;

	i = 0;
	triple = ft_split(field, ',');
	if (!triple)
		return ((t_color) {-1, -1, -1});
	while(triple[i])
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
	char **triple;
	int		i;
	t_vec3	c;

	i = 0;
	triple = ft_split(field, ',');
	if (!triple)
		return ((t_vec3) {INFINITY, INFINITY, INFINITY});
	while(triple[i])
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
	char **fields;

	fields = ft_split(line, ' ');
	if (!fields)
		return (0);
	ambient->ratio = ft_atod(fields[1]);	
	ambient->color = get_color_field(fields[2]);
	if (ambient->color.r == -1.0L && free_split(fields))
		return (0);
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
		while(x < WIDTH)
		{
			ray.x = - width / 2.0L + x * xstep + 0.5 * xstep;
			ray.y = 0.5 - y * ystep - 0.5 * ystep;
			ray.z = 1;
			// print_vec3(ray);
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
	char **fields;

	fields = ft_split(line, ' ');
	if (!fields)
		return (0);
	camera->v_position = get_vector_field(fields[1]);
	if (camera->v_position.x == INFINITY && free_split(fields))
		return (0);
	camera->v_direction = get_vector_field(fields[2]);
	if (camera->v_direction.x == INFINITY && free_split(fields))
		return (0);
	camera->fov = ft_atod(fields[3]);
	set_cam_rays(camera->fov, camera->rays);
	camera->m_camera_world = object_to_world(camera->v_direction, camera->v_position);
	invert_matrix(camera->m_camera_world.m, camera->m_world_camera.m);
	if (!d_nearly_equal(1.0L, vec3_dot(camera->v_direction, camera->v_direction))
		&& free_split(fields) && write(2, "Camera Orientation vector must be normalized\n", 46))
		return (0);
	free_split(fields);
	return (1);
}

int	load_light(char *line, t_light *light)
{
	char **fields;

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
	char **fields;

	object->type = 's';
	object->sphere = malloc(sizeof(t_sphere));
	if (!object->sphere)
		return (0);
	fields = ft_split(line, ' ');
	if (!fields)
		return (0);
	object->sphere->position = get_vector_field(fields[1]);
	if (object->sphere->position.x == INFINITY && free_split(fields))
		return (0);
	object->sphere->radius = ft_atod(fields[2]) / 2;
	object->sphere->color = get_color_field(fields[3]);
	if (object->sphere->color.r== -1 && free_split(fields))
		return (0);
	free_split(fields);
	return (1);
}

int	load_plane(char *line, t_object *plane)
{
	char **fields;

	plane->type = 'p';
	plane->plane = malloc(sizeof(t_plane));
	if (!plane->plane)
		return (0);
	fields = ft_split(line, ' ');
	if (!fields)
		return (0);
	plane->plane->position = get_vector_field(fields[1]);
	if (plane->plane->position.x == INFINITY && free_split(fields))
		return (0);
	plane->plane->normal_vec = get_vector_field(fields[2]);
	if (plane->plane->position.x == INFINITY && free_split(fields))
		return (0);
	plane->plane->color = get_color_field(fields[3]);
	if (plane->plane->color.r== -1 && free_split(fields))
		return (0);
	if (!d_nearly_equal(1.0L, vec3_dot(plane->plane->normal_vec, plane->plane->normal_vec))
		&& free_split(fields) && write(2, "Plane Orientation vector must be normalized\n", 45))
		return (0);
	free_split(fields);
	return (1);
}

int	load_cylinder(char *line, t_object *object)
{
	char **fields;

	object->type = 'c';
	object->cylinder = malloc(sizeof(t_cylinder));
	if (!object->cylinder)
		return (0);
	fields = ft_split(line, ' ');
	if (!fields)
		return (0);
	object->cylinder->position = get_vector_field(fields[1]);
	if (object->cylinder->position.x == INFINITY && free_split(fields))
		return (0);
	object->cylinder->orientation = get_vector_field(fields[2]);
	if (object->cylinder->position.x == INFINITY && free_split(fields))
		return (0);
	object->cylinder->diameter = ft_atod(fields[3]);
	object->cylinder->height = ft_atod(fields[4]);
	object->cylinder->color = get_color_field(fields[5]);
	if (object->cylinder->color.r== -1 && free_split(fields))
		return (0);
	object->cylinder->m_to_world = object_to_world(object->cylinder->orientation, object->cylinder->position);
	invert_matrix(object->cylinder->m_to_world.m, object->cylinder->m_to_cylinder.m);
	if (!d_nearly_equal(1.0L, vec3_dot(object->cylinder->orientation, object->cylinder->orientation))
		&& free_split(fields) && write(2, "Cylinder Orientation vector must be normalized\n", 48))
		return (0);
	free_split(fields);
	return (1);
}

/*sphere 0, plane 1, cylinder 2*/
t_scene	*get_scene(char *filename)
{
	int	fd;
	t_scene	*scene;
	char *line;
	int	idx;

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
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!ft_strncmp(line, "A ", 2) && !load_ambient(line, &scene->ambient_l)
			&& free_1(line) && !close(fd))
			return (NULL);
		else if (!ft_strncmp(line, "C ", 2) && !load_camera(line, &scene->camera)
			&& free_1(line) && !close(fd))
			return (NULL);
		else if (!ft_strncmp(line, "L ", 2) && !load_light(line, &scene->light)
			&& free_1(line) && !close(fd))
			return (NULL);
		else if (!ft_strncmp(line, "sp ", 3)  && !load_sphere(line, ft_objat(scene->objects, idx++)) && !close(fd))
			return (NULL);
		else if (!ft_strncmp(line, "pl ", 3)  && !load_plane(line, ft_objat(scene->objects, idx++)) && !close(fd))
			return (NULL);
		else if (!ft_strncmp(line, "cy ", 3)  && !load_cylinder(line, ft_objat(scene->objects, idx++)) && !close(fd))
			return (NULL);
		free(line);
		line = get_next_line(fd);
	}
	return (scene);
}