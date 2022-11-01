/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecoperations3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:58:26 by marius            #+#    #+#             */
/*   Updated: 2022/10/28 17:13:32 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vecmath.h"

int vec3_is_nearly_equal(t_vec3 v0, t_vec3 v1)
{
	return fabs(v0.x - v1.x) < EPSILON && fabs(v0.y - v1.y) < EPSILON && fabs(v0.z - v1.z) < EPSILON;
}

int vec3_is_equal(t_vec3 v0, t_vec3 v1)
{
	return v0.x == v1.x && v0.y == v1.y && v0.z == v1.z;
}
