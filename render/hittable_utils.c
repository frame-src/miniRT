/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:21:05 by mawinter          #+#    #+#             */
/*   Updated: 2022/12/13 12:22:28 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	norm_set_hit_record(t_hit_info *hit_record, t_ray ray, t_vec3 norm)
{
	double	direction;

	vec3_normalize(&norm);
	hit_record->normal = norm;
	direction = vec3_dot(ray.direction, norm);
	if (direction < 0)
		return ;
	else
		hit_record->normal = vec3_mult(-1, norm);
}

void	fill_hirecord(t_ray ray, t_cylinder *cylinder,
		double ts[3], t_hit_info *hit_record)
{
	if (ts[0] >= 0 && (ts[1] == -1.0L || ts[0] <= ts[1])
		&& (ts[2] == -1.0L || ts[0] <= ts[2]))
	{
		hit_record->t = ts[0];
		norm_set_hit_record(hit_record, ray, cylinder->orientation);
		return ;
	}
	if (ts[1] >= 0 && (ts[2] == -1.0L || ts[1] <= ts[2])
		&& (ts[0] == -1.0L || ts[1] <= ts[0]))
	{
		hit_record->t = ts[1];
		norm_set_hit_record(hit_record, ray, cylinder->orientation);
		return ;
	}
	else if (ts[2] >= 0)
	{
		hit_record->t = ts[2];
		norm_set_hit_record(hit_record, ray, cylinder_get_surface_normal(
				cylinder, vec3_add(ray.origin, vec3_mult(ts[2],
						ray.direction))));
		return ;
	}
	hit_record->t = ts[0];
}
