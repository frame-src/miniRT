/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:57:04 by mawinter          #+#    #+#             */
/*   Updated: 2022/10/29 03:32:31 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define TRUE 1
# define FALSE 0
# define WIDTH 1080
# define HEIGHT 720
# include <string.h>
# include "MLX42/MLX42.h"
# include "vector/vecmath.h"
# include "utility/utils.h"
# include "objects/objects.h"
# include "input/input.h"

/*						MiniRT							*/
typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*g_img;
	t_scene		*scene;
}				t_data;


/*	input_check_elememt2.c	*/
int				valid_cylinder(char *line);

/*	input_utils.c	*/
int				i_identifier(char **identifiers, char *identifier);

#endif