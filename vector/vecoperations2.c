/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecoperations2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 21:40:58 by marius            #+#    #+#             */
/*   Updated: 2022/11/01 18:18:25 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vecmath.h"

t_vec3 vec3_sub(t_vec3 v0, t_vec3 v1)
{
	t_vec3 cross;
    
	cross.x = v0.x - v1.x;
	cross.y = v0.y - v1.y;
	cross.z = v0.z - v1.z;
    return (cross);
}

t_vec3 vec3_mult(double t, t_vec3 v)
{
	t_vec3 cross;
    
	cross.x = t * v.x;
	cross.y = t * v.y;
	cross.z = t * v.z;
    return (cross);
}


t_vec3 vec3_div(double t, t_vec3 v)
{
	t_vec3 cross;

	cross.x = t / v.x;
	cross.y = t / v.y;
	cross.z = t / v.z;
    return (cross);
}

t_vec3 vec3_matrix_mult(t_matrix4x4 m, t_vec3 v, int is_dir)
{
	t_vec3	res;

	if (is_dir)
		is_dir = 0;
	else
		is_dir = 1;
	res.x = v.x * m.m[0] + v.y * m.m[1] + v.z * m.m[2] + is_dir * m.m[3];
	res.y = v.x * m.m[4] + v.y * m.m[5] + v.z * m.m[6] + is_dir * m.m[7];
	res.z = v.x * m.m[8] + v.y * m.m[9] + v.z * m.m[10] + is_dir * m.m[11];

	return (res);
}

void	vec3_set(t_vec3 *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}