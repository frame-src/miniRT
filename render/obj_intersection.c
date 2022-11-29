/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:45:02 by mawinter          #+#    #+#             */
/*   Updated: 2022/11/29 18:21:07 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	get_sphere_intersect(t_hit_info *hit_rec, t_sphere *sphere, t_ray ray)
{
	double solution[2];

	t_vec3 oc = vec3_sub(sphere->position, ray.origin);
	double A = 1.0f;
	double B = 2.0 * vec3_dot(oc, ray.direction);
	double C = vec3_dot(oc, oc) - (sphere->radius) * (sphere->radius);
	double discriminant = B * B - 4 * A * C;
	if (discriminant < 0)
	{
		hit_rec->t = -1.0L;
			return ;
	}
	solution[0] = (-B - sqrt(discriminant)) / (2.0 * A);
	solution[1] = (-B + sqrt(discriminant)) / (2.0 * A);
	norm_set_hit_record(&hit_rec, ray, oc);
	if (solution[0] < 0.0L)
	{
		if (solution[1] < 0.0L)
		{
			hit_rec->t = -1.0L;
			return ;
		}
		hit_rec->t = solution[1];
		return ;
	}
	hit_rec->t = solution[0];
}

void	get_plane_intersect(t_hit_info *hit_rec, t_plane *plane, t_ray ray)
{
	double	denom;
	double	nom;
	t_vec3	tmp;

	vec3_normalize(&ray.direction);
	denom = vec3_dot(plane->normal_vec, ray.direction);
	if (fabs(denom) > EPSILON)
	{
		tmp = vec3_sub(plane->position, ray.origin);
		nom = vec3_dot(tmp, plane->normal_vec);
		hit_rec->t = (nom / denom);
		norm_set_hit_record(&hit_rec, ray, plane->normal_vec);
		return;
	}
	hit_rec->t = -1.0L;
}

/*
	iterator through the list;
	store the index of the node with the smallest t;
	return the object stored at the node[index];
*/
void	obj_get_nearest(t_hit_info *hit_record, t_object *cur_obj, t_ray ray)
{
	t_hit_info	tmp_record;
	int			index;
	int			minimum_index;
	t_object	*head;

	head = cur_obj;
	index = 0;
	minimum_index = -1;
	tmp_record.t = -1;
	while (cur_obj)
	{
		if (cur_obj->type == 's')
		{
			tmp_record.object = cur_obj;
			get_sphere_intersect(&tmp_record, cur_obj->sphere, ray);
			if (tmp_record.t >= 0.0L && tmp_record.t < hit_record->t)
			{
				*hit_record = tmp_record;
				minimum_index = index;
			}
		}
		else if (cur_obj->type == 'p')
		{
			tmp_record.object = cur_obj;
			get_plane_intersect(&tmp_record, cur_obj->plane, ray);
			if (tmp_record.t >= 0.0L && tmp_record.t < hit_record->t)
			{
				*hit_record = tmp_record;
				minimum_index = index;
			}
		}
		else if (cur_obj->type =='c')
		{
			tmp_record.object = cur_obj;
			get_cylinder_intersect(&tmp_record, cur_obj->cylinder, ray);
			if (tmp_record.t >= 0.0L && tmp_record.t < hit_record->t)
			{
				*hit_record = tmp_record;
				minimum_index = index;
			}
		}
		index++;
		cur_obj = cur_obj->next;
	}
	if (minimum_index == -1)
		hit_record->object = NULL;
}
