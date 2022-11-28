/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:45:02 by mawinter          #+#    #+#             */
/*   Updated: 2022/11/28 19:37:46 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

double	get_sphere_intersect( t_sphere *sphere, t_ray ray)
{
	double res1;
	double res2;

	t_vec3 oc = vec3_sub(ray.origin, sphere->position);
	double A = 1.0f;
	double B = 2.0 * vec3_dot(oc, ray.direction);
	double C = vec3_dot(oc, oc) - (sphere->radius) * (sphere->radius);
	double discriminant = B * B - 4 * A * C;
	if (discriminant < 0)
		return (-1.0);
	res1 = (-B - sqrt(discriminant)) / (2.0 * A);
	res2 = (-B + sqrt(discriminant)) / (2.0 * A);
	if (res1 < 0.0L)
	{
		if (res2 < 0.0L)
			return (-1.0L);
		return (res2);
	}
	return (res1);
}

double	get_plane_intersect( t_plane *plane, t_ray ray)
{
	//are the value already normalized?
	double	denom;
	double	nom;
	t_vec3	tmp;
	
	vec3_normalize(&ray.direction);
	denom = vec3_dot(plane->normal_vec, ray.direction);
	if (fabs(denom) > EPSILON)
	{
		tmp = vec3_sub(plane->position, ray.origin);
		nom = vec3_dot(tmp, plane->normal_vec);
		// printf("plane: t: %f\n", nom / denom);
		return (nom / denom);
	}
	else
		return (-1.0L);
}


t_object *obj_get_nearest(t_object *list, t_ray ray, double *t)
{
	double		tmp;
	int			idx;
	int			minidx;
	t_object	*head;

	head = list;
	idx = 0;
	minidx = -1;
	tmp = -1.0L;
	// printf("START\n");
	while (list)
	{
		// printf("type %c\n", list->type);
		if (list->type == 's')
		{
			tmp = get_sphere_intersect(list->sphere, ray);
			if (tmp >= 0.0L && tmp < *t)
			{
				*t = tmp;
				minidx = idx;
			}
		}
		else if (list->type == 'p')
		{
			tmp = get_plane_intersect(list->plane, ray);
			if (tmp >= 0.0L && tmp < *t)
			{
				*t = tmp;
				minidx = idx;
			}
		}
		else if (list->type =='c')
		{
			tmp = get_cylinder_intersect(list->cylinder, ray);
			if (tmp >= 0.0L && tmp < *t)
			{
				*t = tmp;
				minidx = idx;
			}
		}
		idx++;
		list = list->next;
	}
	if (minidx == -1)
		return (NULL);
	return (ft_objat(head, minidx));
}

