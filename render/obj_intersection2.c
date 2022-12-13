/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intersection2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:16:14 by mawinter          #+#    #+#             */
/*   Updated: 2022/12/13 15:17:46 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	if_sphere(t_hit_info *hit_record, t_object *cur_obj,
			t_ray ray, int idxs[2])
{
	t_hit_info	tmp_record;

	tmp_record.t = -1;
	tmp_record.object = NULL;
	if (cur_obj->type == 's')
	{
		tmp_record.object = cur_obj;
		get_sphere_intersect(&tmp_record, cur_obj->sphere, ray);
		if (tmp_record.t >= 0.0L && tmp_record.t < hit_record->t)
		{
			*hit_record = tmp_record;
			idxs[0] = idxs[1];
		}
	}
}

void	if_plane(t_hit_info *hit_record, t_object *cur_obj,
			t_ray ray, int idxs[2])
{
	t_hit_info	tmp_record;

	tmp_record.t = -1;
	tmp_record.object = NULL;
	tmp_record.object = cur_obj;
	get_plane_intersect(&tmp_record, cur_obj->plane, ray);
	if (tmp_record.t >= 0.0L && tmp_record.t < hit_record->t)
	{
		*hit_record = tmp_record;
		idxs[0] = idxs[1];
	}
}

void	if_cyl(t_hit_info *hit_record, t_object *cur_obj, t_ray ray,
			int idxs[2])
{
	t_hit_info	tmp_record;

	tmp_record.t = -1;
	tmp_record.object = NULL;
	tmp_record.object = cur_obj;
	get_cylinder_intersect(&tmp_record, cur_obj->cylinder, ray);
	if (tmp_record.t >= 0.0L && tmp_record.t < hit_record->t)
	{
		*hit_record = tmp_record;
		idxs[0] = idxs[1];
	}
}
