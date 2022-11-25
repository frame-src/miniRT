/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:45:02 by mawinter          #+#    #+#             */
/*   Updated: 2022/11/25 15:38:54 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

double	get_sphere_intersect(t_ray ray, t_sphere *sphere)
{
	t_vec3 oc = vec3_sub(ray.origin, sphere->position);
	double A = 1.0f;
	double B = 2.0 * vec3_dot(oc, ray.direction);
	double C = vec3_dot(oc, oc) - (sphere->radius) * (sphere->radius);
	double discriminant = B * B - 4 * A * C;
	if (discriminant < 0)
		return (-1.0);
	return (-B - sqrt(discriminant)) / (2.0 * A);
}

double	get_cylinder_intersect(t_ray ray, t_cylinder *cylinder)
{
	t_ray l_ray;

	l_ray.direction = vec3_matrix_mult(cylinder->m_to_cylinder, ray.direction, 1);
	l_ray.origin = vec3_matrix_mult(cylinder->m_to_cylinder, ray.origin, 0);

	double a = pow(ray.direction.x, 2) + pow(ray.direction.y, 2);
	double b = 2.0L * ray.origin.x * ray.direction.x + 2.0L * ray.origin.y * ray.direction.y;
	double c = -pow(cylinder->diameter / 2.0L, 2) + pow(ray.origin.x, 2) + pow(ray.origin.y, 2);
	double discriminant = sqrt(b) - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	return (-B - sqrt(discriminant)) / (2.0 * A);
}

t_object *obj_get_nearest(t_object *list, t_ray ray, double *t)
{
	double	tmp;
	int		idx;
	int		minidx;
	t_object	*head;

	head = list;
	idx = 0;
	minidx = 0;
	tmp = -1.0l;
	while (list)
	{
		if (list->type == 's')
		{
			tmp = get_sphere_intersect(ray, list->sphere);
			if (tmp >= 0.0L && tmp < *t)
			{
				*t = tmp;
				minidx = idx;
			}
		}
		else if (list->type == 'p')
		{
			tmp = get_plane_intersect(ray, list->plane);
			if (tmp >= 0.0L && tmp < *t)
			{
				*t = tmp;
				minidx = idx;
			}
		}
		else if (list->type =='c')
		{
			tmp = get_cylinder_intersect(ray, list->plane);
			if (tmp >= 0.0L && tmp < *t)
			{
				*t = tmp;
				minidx = idx;
			}
		}
		idx++;
		list = list->next;
	}
	return (ft_objat(head, minidx));
}

