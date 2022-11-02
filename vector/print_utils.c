/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:30:16 by marius            #+#    #+#             */
/*   Updated: 2022/11/01 17:25:13 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vecmath.h"
#include <stdio.h>

void    print_matrix(t_matrix4x4 m)
{
    printf("%10f  %10f  %10f  %10f\n", m.m[0], m.m[1], m.m[2], m.m[3]);
    printf("%10f  %10f  %10f  %10f\n", m.m[4], m.m[5], m.m[6], m.m[7]);
    printf("%10f  %10f  %10f  %10f\n", m.m[8], m.m[9], m.m[10], m.m[11]);
    printf("%10f  %10f  %10f  %10f\n", m.m[12], m.m[13], m.m[14], m.m[15]);
}

void    print_vec3(t_vec3 v)
{
    printf("%10f  ", v.x);
    printf("%10f  ", v.y);
    printf("%10f\n", v.z);
}