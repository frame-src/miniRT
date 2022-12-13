/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_surface_normal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:57:12 by mawinter          #+#    #+#             */
/*   Updated: 2022/12/13 11:43:31 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_vec3	get_surface_normal(t_object *obj, t_vec3 hitpoint, t_light *light)
{
	t_vec3	sfnormal;
	t_vec3	trans_hit;
	t_vec3	cyl_start;

	if (obj->type == 's')
	{
		sfnormal = vec3_sub(hitpoint, obj->sphere->position);
		vec3_normalize(&sfnormal);
		return (sfnormal);
	}
	if (obj->type == 'p')
	{
		sfnormal = obj->plane->normal_vec;
		if (vec3_dot(sfnormal, vec3_sub(hitpoint, light->position)) < 0)
			sfnormal = vec3_mult(-1.0L, sfnormal);
		return (sfnormal);
	}
	trans_hit = vec3_matrix_mult(obj->cylinder->m_to_cylinder, hitpoint, 0);
	cyl_start.x = 0;
	cyl_start.y = 0;
	cyl_start.z = trans_hit.z;
	sfnormal = vec3_sub(trans_hit, cyl_start);
	vec3_normalize(&sfnormal);
	sfnormal = vec3_matrix_mult(obj->cylinder->m_to_world, sfnormal, 1);
	return (sfnormal);
}
