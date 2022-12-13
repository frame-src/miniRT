/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:22:36 by mawinter          #+#    #+#             */
/*   Updated: 2022/12/13 12:22:54 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../objects/objects.h"
#include "render.h"

t_ray	get_light_ray(t_hit_info hit_record, t_ray *ray, t_scene *scene)
{
	t_vec3	hitpoint;
	t_ray	light_ray;

	hitpoint = vec3_add(ray->origin, vec3_mult(hit_record.t, ray->direction));
	hitpoint = move_by_vec_ratio(hitpoint, EPSILON, hit_record.normal);
	light_ray.origin = hitpoint;
	light_ray.direction = vec3_sub(scene->light.position, hitpoint);
	vec3_normalize(&light_ray.direction);
	return (light_ray);
}
