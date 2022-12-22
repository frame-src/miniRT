/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_calcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:41:03 by mawinter          #+#    #+#             */
/*   Updated: 2022/12/22 15:12:27 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../objects/objects.h"

t_color	color_of_object(t_object *obj)
{
	if (obj->type == 's')
		return (obj->sphere->color);
	if (obj->type == 'p')
		return (obj->plane->color);
	if (obj->type == 'c')
		return (obj->cylinder->color);
	printf("No object Found");
	return ((t_color){0, 0, 0});
}

t_color	color_add(t_color base, t_color addon)
{
	t_color	newcolor;

	newcolor.r = base.r + addon.r;
	newcolor.g = base.g + addon.g;
	newcolor.b = base.b + addon.b;
	return (newcolor);
}

t_color	color_mult_ratio(t_color color, double ratio)
{
	t_color	newcolor;

	newcolor.r = color.r * ratio;
	newcolor.g = color.g * ratio;
	newcolor.b = color.b * ratio;
	return (newcolor);
}
