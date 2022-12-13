/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_position.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:43:18 by mawinter          #+#    #+#             */
/*   Updated: 2022/12/13 11:41:33 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_vec3	get_obj_position(t_object *obj)
{
	if (obj->type == 's')
		return (obj->sphere->position);
	if (obj->type == 'p')
		return (obj->plane->position);
	if (obj->type == 'c')
		return (obj->cylinder->position);
	return ((t_vec3){0, 0, 0});
}
