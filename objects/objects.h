/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 23:03:23 by marius            #+#    #+#             */
/*   Updated: 2022/12/09 11:47:33 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# include <stdio.h>
# include "../vector/vecmath.h"
# include <stdbool.h>

# define WIDTH 1600
# define HEIGHT 900

typedef struct s_vec3		t_vec3;
typedef struct s_vec3		t_point3;
typedef struct s_hit_info	t_hit_info;
typedef struct s_object		t_object;

/*
	Hit record; 
	Because maybe it is easier if we store the t and some information about the hit. 
	For processing the lights and the colors later;
*/
typedef struct s_hit_info
{
	t_vec3		normal;
	double		t;
	t_object	*object;
}				t_hit_info;

typedef struct  s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}				t_ray;

typedef struct	s_color
{
    int   r;
    int   g;
    int   b;
}				t_color;

typedef struct s_ambient
{
	double		ratio;
	t_color		color;
	t_color		ratiocolor;
}				t_ambient;

typedef struct s_camera
{
	t_vec3		rays[HEIGHT][WIDTH];
	t_vec3		position;
	t_vec3		direction;
	int			fov;

	t_matrix4x4	m_camera_world;
	t_matrix4x4	m_world_camera;
}				t_camera;

typedef struct s_light
{
	t_vec3	position;
	double	brightness_ratio;
	t_color	color;
}				t_light;

typedef struct s_sphere
{
	t_vec3		position;
	double		radius;
	t_color		color;
	// t_hit_info	hit_rec;
}				t_sphere;

typedef struct s_plane
{
	t_vec3		position;
	t_vec3		normal_vec;
	t_color		color;
	// t_hit_info	hit_rec;
}				t_plane;

typedef struct s_cylinder
{
	t_vec3		position;
	t_vec3		orientation;
	t_color		color;

	double		diameter;
	double		height;
	t_matrix4x4	m_to_cylinder;
	t_matrix4x4	m_to_world;
	// t_hit_info	hit_rec;
}				t_cylinder;

typedef struct s_object
{
	char		type;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	struct s_object *next;
}				t_object;

typedef struct s_scene
{
	t_ambient	ambient_l;
	t_camera	camera;
	t_light		light;
	t_object	*objects;
}				t_scene;


t_matrix4x4	object_to_world(t_vec3 v_direction, t_vec3 v_position);
/* print */
void	print_ray(t_ray ray);
int		print_scene(t_scene *scene);
t_vec3	get_obj_position(t_object *obj);
t_vec3	get_surface_normal(t_object *obj, t_vec3 hitpoint, t_light *light);
#endif