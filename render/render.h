/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:03:26 by marius            #+#    #+#             */
/*   Updated: 2022/11/28 21:20:35 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include "../objects/objects.h"
#include "../utility/utils.h"

t_matrix4x4	camera_to_world(t_vec3 v_direction, t_vec3 v_position);

/*					sphere_intersect.c							*/
double	get_sphere_intersect(t_sphere *sphere, t_ray ray);
t_object *obj_get_nearest(t_object *list, t_ray ray, double *t);
double	get_cylinder_intersect(t_cylinder *cylinder, t_ray ray);
double	get_plane_intersect( t_plane *plane, t_ray ray);
t_ray	get_light_ray(double t, t_ray *ray, t_scene *scene, t_object *cur_obj);
t_color	color_mult_ratio(t_color color, double ratio);
t_vec3	move_by_vec_ratio(t_vec3 pos, double t, t_vec3 along);
t_color color_add(t_color base, t_color addon);
#endif