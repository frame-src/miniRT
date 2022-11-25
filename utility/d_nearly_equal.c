/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_nearly_equal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:48:48 by mawinter          #+#    #+#             */
/*   Updated: 2022/11/25 18:03:30 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vector/vecmath.h"

int	d_nearly_equal(double d1, double d2)
{
	return (fabs(d1 - d2) < EPSILON);
}