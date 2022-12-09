/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:51:48 by mawinter          #+#    #+#             */
/*   Updated: 2022/12/09 11:48:20 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	put_color_pixel(t_data *data, int x, int y, t_color color)
{
	mlx_put_pixel(data->g_img, x, y, color.r << 24 | color.g << 16 | color.b << 8 | 255);
}

t_color	color_of_object(t_object *obj)
{
	// if (!obj)
		// return ((t_color) {0,0,0});
	if (obj->type == 's')
		return (obj->sphere->color);
	if (obj->type == 'p')
		return (obj->plane->color);
	if (obj->type == 'c')
		return (obj->cylinder->color);
	printf("No object Found");
	return ((t_color) {0,0,0});
}

void	hook(void *param)
{
	t_data	*data;
	data= NULL;
	if(data)
		data = NULL;
	int 			y;
	int 			x;
	t_color			color;
	t_ray			light_ray;
	t_ray			ray;
	t_hit_info		hit_record;
	t_hit_info		new_hit;

	color.r = 0; color.g = 0; color.b = 255;
	data = param;
	y = 0;
	x = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{

			ray.origin = data->scene->camera.position;
			ray.direction = vec3_matrix_mult(data->scene->camera.m_camera_world,
												data->scene->camera.rays[y][x], 1);
			hit_record.t = INFINITY;
			new_hit.t = INFINITY;

			obj_get_nearest(&hit_record, data->scene->objects, ray);
			if (!hit_record.object)
				put_color_pixel(data, x, y,  (t_color) {0,0,0});	
			else if (hit_record.object)
			{
				light_ray = get_light_ray(hit_record, &ray, data->scene);
				obj_get_nearest(&new_hit, data->scene->objects, light_ray);
				if(new_hit.object)
				{
					put_color_pixel(data, x, y, (t_color) {0,0,0});
				}
				else
				{
					double nom = vec3_dot(light_ray.direction, hit_record.normal);
					double denom = vec3_length(light_ray.direction);
					double res =(nom / denom);
					put_color_pixel(data, x, y, color_mult_ratio(color_of_object(hit_record.object), res));
				}
			}
			++x;
		}
		++y;
	}
}


void	free_data()
{
	return;
}


int	main(int argc, char **argv)
{
	t_data *data;

	if (argc != 2 || (argc == 2 && !valid_input(argv[1])))
		return (1);
	data = malloc(sizeof(t_data));
	data->scene = get_scene(argv[1]);
	if (!data->scene)
	{
		printf("GET SCENE UNSUCCESSFULL\n");
		free(data);
		return (1);
	}
	print_scene(data->scene);
	printf("GET SCENE SUCCESSFULL\n");
	t_ray ray;
	ray.origin = (t_point3) {0, 0, 0};
	ray.direction = (t_vec3) {0, 1, 1};
	data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	if (!data->mlx)
		exit(EXIT_FAILURE);
	data->g_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	memset(data->g_img->pixels, 255, data->g_img->width * data->g_img->height * sizeof(int));
	mlx_image_to_window(data->mlx, data->g_img, 0, 0);
	mlx_loop_hook(data->mlx, &hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}