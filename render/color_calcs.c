/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_calcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:41:03 by mawinter          #+#    #+#             */
/*   Updated: 2022/11/28 18:58:10 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../objects/objects.h"

t_color	color_mult_ratio(t_color color, double ratio)
{
	t_color newcolor;

	newcolor.r = color.r * ratio;
	newcolor.g = color.g * ratio;
	newcolor.b = color.b * ratio;
	return (newcolor);
}