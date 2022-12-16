/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:45:02 by mawinter          #+#    #+#             */
/*   Updated: 2022/12/16 17:55:52 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	get_sphere_intersect_helper(double all[6], t_hit_info *hit_rec,
		t_sphere *sphere, t_ray ray)
{
	if (all[4] < 0.0L)
	{
		if (all[5] < 0.0L)
		{
			hit_rec->t = -1.0L;
			return ;
		}
		hit_rec->t = all[5];
		norm_set_hit_record(hit_rec, ray, vec3_sub(vec3_add(ray.origin,
					vec3_mult(all[5], ray.direction)), sphere->position));
		return ;
	}
	norm_set_hit_record(hit_rec, ray, vec3_sub(vec3_add(ray.origin,
				vec3_mult(all[4], ray.direction)), sphere->position));
	hit_rec->t = all[4];
}

void	get_sphere_intersect(t_hit_info *hit_rec, t_sphere *sphere, t_ray ray)
{
	double	all[6];
	t_vec3	oc;

	oc = vec3_sub(ray.origin, sphere->position);
	all[0] = 1.0f;
	all[1] = 2.0 * vec3_dot(oc, ray.direction);
	all[2] = vec3_dot(oc, oc) - (sphere->radius) * (sphere->radius);
	all[3] = all[1] * all[1] - 4 * all[0] * all[2];
	if (all[3] < 0)
	{
		hit_rec->t = -1.0L;
		return ;
	}
	all[4] = (-all[1] - sqrt(all[3])) / (2.0 * all[0]);
	all[5] = (-all[1] + sqrt(all[3])) / (2.0 * all[0]);
	get_sphere_intersect_helper(all, hit_rec, sphere, ray);
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
		norm_set_hit_record(hit_rec, ray, plane->normal_vec);
		return ;
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
	int			idxs[2];

	idxs[1] = 0;
	idxs[0] = -1;
	while (cur_obj)
	{
		if (cur_obj->type == 's')
			if_sphere(hit_record, cur_obj, ray, idxs);
		else if (cur_obj->type == 'p')
			if_plane(hit_record, cur_obj, ray, idxs);
		else if (cur_obj->type == 'c')
			if_cyl(hit_record, cur_obj, ray, idxs);
		idxs[1]++;
		cur_obj = cur_obj->next;
	}
	if (idxs[0] == -1)
		hit_record->object = NULL;
}
