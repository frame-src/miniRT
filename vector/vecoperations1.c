/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecoperations1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 21:02:49 by marius            #+#    #+#             */
/*   Updated: 2022/11/01 17:11:25 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vecmath.h"

double vec3_length(t_vec3 v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

double   vec3_dot(t_vec3 v0, t_vec3 v1)
{
    return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}
void    vec3_normalize(t_vec3 *v)
{
	double length;

    length = vec3_length(*v);
	v->x = v->x / length;
	v->y = v->y / length;
	v->z = v->z / length;
}

t_vec3 vec3_cross(t_vec3 v0, t_vec3 v1)
{
	t_vec3 cross;
    
	cross.x = v0.y * v1.z - v0.z * v1.y;
	cross.y = v0.z * v1.x - v0.x * v1.z;
	cross.z = v0.x * v1.y - v0.y * v1.x;
    return (cross);
}

t_vec3 vec3_add(t_vec3 v0, t_vec3 v1)
{
	t_vec3 cross;
    
	cross.x = v0.x + v1.x;	
	cross.y = v0.y + v1.y;
	cross.z = v0.z + v1.z;
    return (cross);
}
