/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:02:38 by mawinter          #+#    #+#             */
/*   Updated: 2022/12/13 12:19:18 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
/*
	checking the body of the cylinder; 

*/
static	double	cylinder_check_limit(t_cylinder *cylinder,
		t_ray l_ray, double t)
{
	double		limits;

	limits = l_ray.origin.z + l_ray.direction.z * t;
	if (limits <= cylinder->height / 2 && limits >= -1 * cylinder->height / 2)
		return (t);
	return (-1.0L);
}

static	double	cylinder_body_equation(t_cylinder *cylinder, t_ray l_ray)
{
	double	solution[2];
	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = pow(l_ray.direction.x, 2) + pow(l_ray.direction.y, 2);
	b = 2.0L * l_ray.origin.x * l_ray.direction.x + 2.0L
		* l_ray.origin.y * l_ray.direction.y;
	c = pow(l_ray.origin.x, 2) + pow(l_ray.origin.y, 2)
		- pow(cylinder->diameter / 2.0L, 2);
	discriminant = pow(b, 2) - (4 * a * c);
	if (discriminant < 0)
		return (-1.0L);
	solution[0] = (-b - sqrt(discriminant)) / (2.0 * a);
	solution[1] = (-b + sqrt(discriminant)) / (2.0 * a);
	if (solution[0] < 0.0L)
	{
		if (solution[1] < 0.0L)
			return (-1.0L);
		return (cylinder_check_limit(cylinder, l_ray, solution[1]));
	}
	return (cylinder_check_limit(cylinder, l_ray, solution[0]));
}

static double	get_disk_intersect(t_hit_info *hit_record,
		t_plane *plane, t_ray ray, double radius)
{
	double	dist;
	t_vec3	hitpoint;
	t_vec3	distancevector;

	get_plane_intersect(hit_record, plane, ray);
	if (hit_record->t == -1.0L)
		return (-1.0L);
	hitpoint = vec3_add(ray.origin, vec3_mult(hit_record->t, ray.direction));
	distancevector = vec3_sub(plane->position, hitpoint);
	dist = vec3_length(distancevector);
	if (dist <= radius)
		return (hit_record->t);
	else
		return (-1.0L);
}

t_vec3	cylinder_get_surface_normal(t_cylinder *cylinder, t_vec3 hitpoint)
{
	t_vec3	surface_normal;
	t_vec3	trans_hit;
	t_vec3	cyl_start;

	trans_hit = vec3_matrix_mult(cylinder->m_to_cylinder, hitpoint, 0);
	cyl_start.x = 0;
	cyl_start.y = 0;
	cyl_start.z = trans_hit.z;
	surface_normal = vec3_sub(trans_hit, cyl_start);
	vec3_normalize(&surface_normal);
	surface_normal = vec3_matrix_mult(cylinder->m_to_world, surface_normal, 1);
	return (surface_normal);
}

void	get_cylinder_intersect(t_hit_info *hit_record,
		t_cylinder *cylinder, t_ray ray)
{
	t_ray		l_ray;
	double		ts[3];
	t_plane		caps[2];

	l_ray.direction = vec3_matrix_mult(cylinder->m_to_cylinder,
			ray.direction, 1);
	l_ray.origin = vec3_matrix_mult(cylinder->m_to_cylinder, ray.origin, 0);
	caps[0].normal_vec = vec3_matrix_mult(cylinder->m_to_cylinder,
			cylinder->orientation, 1);
	caps[0].position = (t_vec3){0, 0, cylinder->height / 2};
	caps[1].normal_vec = vec3_matrix_mult(cylinder->m_to_cylinder,
			cylinder->orientation, 1);
	caps[1].position = (t_vec3){0, 0, -cylinder->height / 2};
	ts[0] = get_disk_intersect(hit_record, &caps[0], l_ray,
			cylinder->diameter / 2.0L);
	ts[1] = get_disk_intersect(hit_record, &caps[1], l_ray,
			cylinder->diameter / 2.0L);
	ts[2] = cylinder_body_equation(cylinder, l_ray);
	fill_hirecord(ray, cylinder, ts, hit_record);
}
