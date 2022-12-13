/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_by_vec_ratio.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:51:49 by mawinter          #+#    #+#             */
/*   Updated: 2022/12/13 14:18:56 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../objects/objects.h"

t_vec3	move_by_vec_ratio(t_vec3 pos, double t, t_vec3 along)
{
	t_vec3	newvec;

	newvec = vec3_add(pos, vec3_mult(t, along));
	return (newvec);
}
