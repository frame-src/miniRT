/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:03:26 by marius            #+#    #+#             */
/*   Updated: 2022/11/24 21:02:16 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include "../objects/objects.h"

t_matrix4x4	camera_to_world(t_vec3 v_direction, t_vec3 v_position);
# define WIDTH 1000
# define HEIGHT 1000

struct typedef s_vec3 t_point;
struct typedef s_vec3 t_point;


#endif