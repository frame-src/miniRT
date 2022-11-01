/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:38:31 by marius            #+#    #+#             */
/*   Updated: 2022/10/29 00:44:58 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_matrix4x4	camera_to_world(t_vec3 v_direction, t_vec3 v_position)
{
    t_matrix4x4	m;
	t_vec3		tmp;
	t_vec3		up;
	t_vec3		right;

	//print_vec3(v_direction);
	vec3_normalize(&v_direction);
	//print_vec3(v_direction);
	if (vec3_is_equal(v_direction, (t_vec3) {0.0f, 1.0f, 0.0f}))
		vec3_set(&tmp, 0.0f, 0.0f, -1.0f );
	else if (vec3_is_equal(v_direction, (t_vec3) {0.0f, -1.0f, 0.0f}))
		vec3_set(&tmp, 0.0f, 0.0f, 1.0f );
	else 
		vec3_set(&tmp, 0.0f, 1.0f, 0.0f);
	right = vec3_cross(tmp, v_direction);
	//print_vec3(right);
	vec3_normalize(&right);
	up = vec3_cross(v_direction, right);
	//print_vec3(up);
	m.m[0][0] = right.x,   m.m[1][0] = right.y,   m.m[2][0] = right.z;  m.m[3][0] = 0.0f;
    m.m[0][1] = up.x,   m.m[1][1] = up.y,   m.m[2][1] = up.z; m.m[3][1] = 0.0f;
    m.m[0][2] = v_direction.x, m.m[1][2] = v_direction.y, m.m[2][2] = v_direction.z; m.m[3][2] = 0.0f;
    m.m[0][3] = v_position.x,    m.m[1][3] = v_position.y,    m.m[2][3] = v_position.z; m.m[3][3] = 1.0f;
	return m;
}