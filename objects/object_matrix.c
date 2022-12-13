/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:38:31 by marius            #+#    #+#             */
/*   Updated: 2022/12/13 11:51:02 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static	void	set_4x4_matrix(t_vec3 right,
	t_vec3 up, t_vec3 v_direction, t_matrix4x4 *m)
{
	(*m).m[0] = right.x;
	(*m).m[4] = right.y;
	(*m).m[8] = right.z;
	(*m).m[12] = 0.0f;
	(*m).m[1] = up.x;
	(*m).m[5] = up.y;
	(*m).m[9] = up.z;
	(*m).m[13] = 0.0f;
	(*m).m[2] = v_direction.x;
	(*m).m[6] = v_direction.y;
	(*m).m[10] = v_direction.z;
	(*m).m[14] = 0.0f;
}

t_matrix4x4	object_to_world(t_vec3 v_direction, t_vec3 v_position)
{
	t_matrix4x4		m;
	t_vec3			tmp;
	t_vec3			up;
	t_vec3			right;

	vec3_normalize(&v_direction);
	if (vec3_is_equal(v_direction, (t_vec3){0.0f, 1.0f, 0.0f}))
		vec3_set(&tmp, 0.0f, 0.0f, -1.0f);
	else if (vec3_is_equal(v_direction, (t_vec3){0.0f, -1.0f, 0.0f}))
		vec3_set(&tmp, 0.0f, 0.0f, 1.0f);
	else
		vec3_set(&tmp, 0.0f, 1.0f, 0.0f);
	right = vec3_cross(tmp, v_direction);
	vec3_normalize(&right);
	up = vec3_cross(v_direction, right);
	set_4x4_matrix(right, up, v_direction, &m);
	m.m[3] = v_position.x;
	m.m[7] = v_position.y;
	m.m[11] = v_position.z;
	m.m[15] = 1.0f;
	return (m);
}
