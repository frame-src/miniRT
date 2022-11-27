/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 23:03:23 by marius            #+#    #+#             */
/*   Updated: 2022/11/26 23:13:10 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# include <stdio.h>
#include "../vector/vecmath.h"

# define WIDTH 500
# define HEIGHT 500

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
	t_color	color;
}				t_ambient;

typedef struct s_camera
{
	t_vec3		rays[HEIGHT][WIDTH];
	t_vec3		v_position;
	t_vec3		v_direction;
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
}				t_sphere;

typedef struct s_plane
{
	t_vec3	position;
	t_vec3	normal_vec;
	t_color	color;
}				t_plane;


typedef struct s_cylinder
{
	t_vec3	position;
	t_vec3	orientation;
	t_color	color;

	double	diameter;
	double	height;
	t_matrix4x4	m_to_cylinder;
	t_matrix4x4	m_to_world;
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

//print
void	print_ray(t_ray ray);
int		print_scene(t_scene *scene);
#endif