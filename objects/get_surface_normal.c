/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_surface_normal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:57:12 by mawinter          #+#    #+#             */
/*   Updated: 2022/11/29 15:00:42 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_vec3 get_surface_normal(t_object *obj, t_vec3 hitpoint, t_light *light)
{
	t_vec3	surface_normal;
	t_vec3	trans_hit;
	t_vec3	cyl_start;


	if (obj->type == 's')
	{
		surface_normal = vec3_sub(hitpoint, obj->sphere->position);
		vec3_normalize(&surface_normal);
		return (surface_normal);
	}
	if (obj->type == 'p')
	{
		surface_normal = obj->plane->normal_vec;
			printf("%f\n", vec3_dot(surface_normal, vec3_sub(hitpoint, light->position)));
		if (vec3_dot(surface_normal, vec3_sub(hitpoint, light->position)) < 0)
			surface_normal = vec3_mult(-1.0L, surface_normal);
		return (surface_normal);
	}
	if (obj->type == 'c')
	{
		trans_hit = vec3_matrix_mult(obj->cylinder->m_to_cylinder, hitpoint, 0);
		cyl_start.x = 0;
		cyl_start.y = 0;
		cyl_start.z = trans_hit.z;
		surface_normal = vec3_sub(trans_hit, cyl_start);
		vec3_normalize(&surface_normal);
		surface_normal = vec3_matrix_mult(obj->cylinder->m_to_world, surface_normal, 1);
		return (surface_normal);
	}
	printf("No object Found");
	return ((t_vec3) {0,0,0});
}