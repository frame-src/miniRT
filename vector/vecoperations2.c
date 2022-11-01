/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecoperations2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 21:40:58 by marius            #+#    #+#             */
/*   Updated: 2022/10/29 01:08:59 by marius           ###   ########.fr       */
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

t_vec3 vec3_matrix_mult(t_matrix4x4 m, t_vec3 v, int pos_or_dir)
{
	t_vec3	res;

	if (pos_or_dir)
		pos_or_dir = 1;
	else
		pos_or_dir = 0;
	res.x = v.x * m.m[0][0] + v.y * m.m[0][1] + v.z * m.m[0][2] + pos_or_dir * m.m[0][3];
	res.y = v.x * m.m[1][0] + v.y * m.m[1][1] + v.z * m.m[1][2] + pos_or_dir * m.m[1][3];
	res.z = v.x * m.m[2][0] + v.y * m.m[2][1] + v.z * m.m[2][2] + pos_or_dir * m.m[2][3];
	return (res);
}

void	vec3_set(t_vec3 *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}