/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:51:48 by mawinter          #+#    #+#             */
/*   Updated: 2023/01/25 11:46:43 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>

#include "../minirt.h"

void	put_color_pixel(t_data *data, int x, int y, t_color color)
{
	t_color	ambient_color;

	ambient_color.r = (data->scene->ambient_l.color.r \
				* data->scene->ambient_l.ratio);
	ambient_color.g = (data->scene->ambient_l.color.g \
				* data->scene->ambient_l.ratio);
	ambient_color.b = (data->scene->ambient_l.color.b \
				* data->scene->ambient_l.ratio);
	if (color.r * data->scene->light.br + ambient_color.r > 255)
		color.r = 255;
	else
		color.r = color.r * data->scene->light.br + ambient_color.r;
	if (color.g * data->scene->light.br + ambient_color.g > 255)
		color.g = 255;
	else
		color.g = color.g * data->scene->light.br + ambient_color.g;
	if (color.b * data->scene->light.br + ambient_color.b > 255)
		color.b = 255;
	else
		color.b = color.b * data->scene->light.br + ambient_color.b;
	mlx_put_pixel(data->g_img, x, y, color.r << 24 | \
		color.g << 16 | color.b << 8 | 255);
}

/*
	object light < object nearest
	0 is old_ray
	1 is new_ray
*/
static bool	is_light_closer(t_data *data, t_hit_info newhit,
		t_hit_info oldhit, t_ray *rays)
{	
	t_vec3	old_hit;
	t_vec3	new_hit;
	t_vec3	oldhit_tolight;
	t_vec3	oldhit_to_newhit;

	old_hit = vec3_add(vec3_mult(oldhit.t, rays[0].direction), rays[0].origin);
	new_hit = vec3_add(vec3_mult(newhit.t, rays[1].direction), rays[1].origin);
	oldhit_tolight = vec3_sub(old_hit, data->scene->light.position);
	oldhit_tolight = move_by_vec_ratio(oldhit_tolight, EPSILON, vec3_mult(-1, oldhit_tolight));
	oldhit_to_newhit = vec3_sub(old_hit, new_hit);
	if (vec3_length(oldhit_tolight) <= vec3_length(oldhit_to_newhit))
		return (true);
	else
		return (false);
}

/*
	light_rays indexes
	0 is old_ray
	1 is new_ray
*/
static void	ray_setter(const int *itr, t_data *data,
	t_hit_info hit_record, t_ray ray)
{
	t_ray			light_rays[2];
	t_hit_info		new_hit;
	double			nom;
	double			denom;
	double			res;

	new_hit.t = INFINITY;
	light_rays[0] = ray;
	light_rays[1] = get_light_ray(hit_record, &ray, data->scene);
	obj_get_nearest(&new_hit, data->scene->objects, light_rays[1]);
	if (new_hit.object && !is_light_closer(data, new_hit,
			hit_record, light_rays))
	{
		put_color_pixel(data, itr[0], itr[1], (t_color){0, 0, 0});
	}
	else
	{
		nom = vec3_dot(light_rays[1].direction, hit_record.normal);
		denom = vec3_length(light_rays[1].direction);
		res = (nom / denom);
		put_color_pixel(data, itr[0], itr[1],
			color_mult_ratio(color_of_object(hit_record.object), res));
	}
}

static t_ray	ray_direction(t_ray ray, t_data *data, int *itr)
{
	ray.origin = data->scene->camera.position;
	ray.direction = vec3_matrix_mult(\
			data->scene->camera.m_camera_world, \
			data->scene->camera.rays[itr[1]][itr[0]], 1);
	return (ray);
}

void	hook(void *param)
{
	t_data			*data;
	int				itr[2];
	t_ray			ray;
	t_hit_info		hit_record;

	data = param;
	itr[0] = 0;
	itr[1] = 0;
	while (itr[1] < HEIGHT)
	{
		itr[0] = 0;
		while (itr[0] < WIDTH)
		{
			ray = ray_direction(ray, data, itr);
			hit_record.t = INFINITY;
			obj_get_nearest(&hit_record, data->scene->objects, ray);
			if (!hit_record.object)
				put_color_pixel(data, itr[0], itr[1], (t_color){0, 0, 0});
			else if (hit_record.object)
				ray_setter(itr, data, hit_record, ray);
			++itr[0];
		}
		++itr[1];
	}
}
