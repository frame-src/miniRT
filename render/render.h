/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:03:26 by marius            #+#    #+#             */
/*   Updated: 2022/12/22 15:11:30 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "../objects/objects.h"
# include "../utility/utils.h"

t_matrix4x4	camera_to_world(t_vec3 v_direction, t_vec3 v_position);
/*					sphere_intersect.c							*/
void		get_sphere_intersect(t_hit_info *hit_record,
				t_sphere *sphere, t_ray ray);
void		obj_get_nearest(t_hit_info *hit_record, t_object *list, t_ray ray);
void		get_cylinder_intersect(t_hit_info *hit_record, t_cylinder *cylinder,
				t_ray ray);
void		get_plane_intersect(t_hit_info *hit_record, t_plane *plane,
				t_ray ray);
t_ray		get_light_ray(t_hit_info hit_record, t_ray *ray, t_scene *scene);
t_color		color_mult_ratio(t_color color, double ratio);
t_vec3		move_by_vec_ratio(t_vec3 pos, double t, t_vec3 along);
t_color		color_add(t_color base, t_color addon);
void		norm_set_hit_record(t_hit_info *hit_record, t_ray ray, t_vec3 norm);
t_vec3		cylinder_get_surface_normal(t_cylinder *cylinder, t_vec3 hitpoint);
void		fill_hirecord(t_ray ray, t_cylinder *cylinder, double ts[3],
				t_hit_info *hit_record);
void		if_sphere(t_hit_info *hit_record, t_object *cur_obj,
				t_ray ray, int idxs[2]);
void		if_plane(t_hit_info *hit_record, t_object *cur_obj,
				t_ray ray, int idxs[2]);
void		if_cyl(t_hit_info *hit_record, t_object *cur_obj, t_ray ray,
				int idxs[2]);
t_color		color_of_object(t_object *obj);
void		hook(void *param);

#endif