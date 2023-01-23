/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:05:33 by frmessin          #+#    #+#             */
/*   Updated: 2023/01/23 12:32:25 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_color	get_color_field(char *field);
int		load_ambient(char *line, t_ambient *ambient);
int		set_cam_rays(int fov, t_vec3 rays[HEIGHT][WIDTH]);

t_color	get_color_field(char *field)
{
	char	**triple;
	int		i;
	t_color	c;

	i = 0;
	triple = ft_split(field, ',');
	if (!triple)
		return ((t_color){-1, -1, -1});
	while (triple[i])
	{
		if (!i)
			c.r = ft_atod(triple[i]);
		else if (i == 1)
			c.g = ft_atod(triple[i]);
		else
			c.b = ft_atod(triple[i]);
		i++;
	}
	free_split(triple);
	return (c);
}

int	load_ambient(char *line, t_ambient *ambient)
{
	char	**fields;

	fields = ft_split(line, ' ');
	if (!fields)
		return (0);
	ambient->ratio = ft_atod(fields[1]);
	ambient->color = get_color_field(fields[2]);
	if (ambient->color.r == -1.0L && free_split(fields))
		return (0);
	ambient->ratiocolor.r = ambient->color.r * ambient->ratio;
	ambient->ratiocolor.g = ambient->color.g * ambient->ratio;
	ambient->ratiocolor.b = ambient->color.b * ambient->ratio;
	free_split(fields);
	return (1);
}

/*
	coord:	x --> coord[0],
			y --> coord[1];
*/
static double	screenratio(void)
{
	return ((double) WIDTH / (double) HEIGHT);
}

static double	step(double l, int i)
{
	double	coord_step[2];

	coord_step[0] = l / WIDTH;
	coord_step[1] = l / HEIGHT;
	return (coord_step[i]);
}

int	set_cam_rays(int fov, t_vec3 rays[HEIGHT][WIDTH])
{
	int		coord[2];
	t_vec3	ray;
	double	l;

	coord[1] = 0;
	if (!fov)
		return (0);
	l = screenratio() * tan(M_PI / 180.0L * (fov / 2));
	if (fov == 180)
		l = 1000;
	while (coord[1] < HEIGHT)
	{
		coord[0] = 0;
		while (coord[0] < WIDTH)
		{
			ray.x = -l / 2.0L + coord[0] * step(l, 0) + 0.5 * step(l, 0);
			ray.y = l * 0.5L - coord[1] * step(l, 1) - 0.5 * step(l, 1);
			ray.z = 1;
			vec3_normalize(&ray);
			rays[coord[1]][coord[0]] = ray;
			coord[0]++;
		}
		coord[1]++;
	}
	return (1);
}
