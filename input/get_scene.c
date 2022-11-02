/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 19:43:16 by marius            #+#    #+#             */
/*   Updated: 2022/11/01 17:52:24 by marius           ###   ########.fr       */
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

	i = -1;
	while (++i < counters[0])
	{
		scene->spheres[i] = ft_calloc(1, sizeof(t_sphere));
		if (!scene->spheres[i])
			return (NULL);
	}
	i = -1;
	while (++i < counters[1])
	{
		scene->planes[i] = ft_calloc(1, sizeof(t_plane));
		if (!scene->planes[i])
			return (NULL);
	}
	i = -1;
	while (++i < counters[2])
	{
		scene->cylinders[i] = ft_calloc(1, sizeof(t_cylinder));
		if (!scene->cylinders[i])
			return (NULL);
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
	printf("sphere counter: %d\n", counters[1]);
	printf("sphere counter: %d\n", counters[2]);
	scene->spheres = ft_calloc(counters[0] + 1, sizeof(t_sphere *));
	if (!scene->spheres && !close(fd))
		return (NULL);
	scene->planes = ft_calloc(counters[1] + 1, sizeof(t_plane *));
	if (!scene->planes && !close(fd))
		return (NULL);
	scene->cylinders = ft_calloc(counters[2] + 1, sizeof(t_cylinder *));
	if (!scene->cylinders && !close(fd))
		return (NULL);
	if (!alloc_objects(scene, counters) && !close(fd))
		return (NULL);
	close(fd);
	return (scene);
}

int	free_scene(t_scene *scene)
{
	if (scene)
	{
		
	free_split_void((void *)scene->spheres);
	free_split_void((void *)scene->planes);
	free_split_void((void *)scene->cylinders);
	free(scene);
	}
	return (0);
}


t_fcolor	get_color_field(char *field)
{
	char **triple;
	int		i;
	t_fcolor	c;

	i = 0;
	triple = ft_split(field, ',');
	if (!triple)
		return ((t_fcolor) {-1, -1, -1});
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


int	set_cam_rays(t_vec3 rays[HEIGHT][WIDTH])
{
	int		x;
	int		y;
	t_vec3	ray;
	double	xratio;
	double	yratio;

	y = 0;
	xratio = 1.0L / WIDTH;
	yratio = 1.0L / HEIGHT;
	while (y < HEIGHT)
	{
		x = 0;
		while(x < WIDTH)
		{
			ray.x = -0.5 + x * xratio + 0.5 * xratio;
			ray.y = 0.5 - y * yratio - 0.5 * yratio;
			ray.z = 1;
			rays[x][y] = ray;
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
	set_cam_rays(camera->rays);
	camera->m_camera_world = camera_to_world(camera->v_direction, camera->v_position);
	invert_matrix(camera->m_camera_world.m, camera->m_world_camera.m);
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

int	load_sphere(char *line, t_sphere *sphere, int *counter)
{
	char **fields;

	*counter = *counter + 1;
	fields = ft_split(line, ' ');
	if (!fields)
		return (0);
	sphere->position = get_vector_field(fields[1]);
	if (sphere->position.x == INFINITY && free_split(fields))
		return (0);
	sphere->diameter = ft_atod(fields[2]);
	sphere->color = get_color_field(fields[3]);
	if (sphere->color.r== -1 && free_split(fields))
		return (0);
	free_split(fields);
	return (1);
}

int	load_plane(char *line, t_plane *plane, int *counter)
{
	char **fields;

	*counter = *counter + 1;
	fields = ft_split(line, ' ');
	if (!fields)
		return (0);
	plane->position = get_vector_field(fields[1]);
	if (plane->position.x == INFINITY && free_split(fields))
		return (0);
	plane->normal_vec = get_vector_field(fields[2]);
	if (plane->position.x == INFINITY && free_split(fields))
		return (0);
	plane->color = get_color_field(fields[3]);
	if (plane->color.r== -1 && free_split(fields))
		return (0);
	free_split(fields);
	return (1);
}

int	load_cylinder(char *line, t_cylinder *cylinder, int *counter)
{
	char **fields;

	*counter = *counter + 1;
	fields = ft_split(line, ' ');
	if (!fields)
		return (0);
	cylinder->position = get_vector_field(fields[1]);
	if (cylinder->position.x == INFINITY && free_split(fields))
		return (0);
	cylinder->normal_vec = get_vector_field(fields[2]);
	if (cylinder->position.x == INFINITY && free_split(fields))
		return (0);

	cylinder->diameter = ft_atod(fields[3]);
	cylinder->height = ft_atod(fields[4]);
		
	cylinder->color = get_color_field(fields[5]);
	if (cylinder->color.r== -1 && free_split(fields))
		return (0);
	free_split(fields);
	return (1);
}

/*sphere 0, plane 1, cylinder 2*/
t_scene	*get_scene(char *filename)
{
	int	fd;
	int	counters[3];
	t_scene	*scene;
	char *line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	scene = alloc_scene(filename);
	ft_memset(counters, 0, 3 * sizeof(int));
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
		else if (!ft_strncmp(line, "sp ", 3)  && !load_sphere(line, scene->spheres[counters[0]], counters) && !close(fd))
			return (NULL);
		else if (!ft_strncmp(line, "pl ", 3)  && !load_plane(line, scene->planes[counters[1]], counters + 1) && !close(fd))
			return (NULL);
		else if (!ft_strncmp(line, "cy ", 3)  && !load_cylinder(line, scene->cylinders[counters[2]], counters + 2) && !close(fd))
			return (NULL);
		free(line);
		line = get_next_line(fd);
	}
		write(1, "out\n", 5);

	return (scene);
}