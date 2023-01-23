/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:05:37 by frmessin          #+#    #+#             */
/*   Updated: 2023/01/23 12:11:53 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int		load_light(char *line, t_light *light);
int		load_cylinder(char *line, t_object *object);
void	load_cyl_help(t_cylinder *cyl, char **fields);
int		load_plane(char *line, t_object *obj);
int		load_sphere(char *line, t_object *object);

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
