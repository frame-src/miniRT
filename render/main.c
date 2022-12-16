/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:51:48 by mawinter          #+#    #+#             */
/*   Updated: 2022/12/16 18:33:02 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// void	put_color_pixel(t_data *data, int x, int y, t_color color)
// {
// 	mlx_put_pixel(data->g_img, x, y, color.r << 24 | color.g << 16 | color.b << 8 | 255);
// }

// t_color	color_of_object(t_object *obj)
// {
// 	if (obj->type == 's')
// 		return (obj->sphere->color);
// 	if (obj->type == 'p')
// 		return (obj->plane->color);
// 	if (obj->type == 'c')
// 		return (obj->cylinder->color);
// 	printf("No object Found");
// 	return ((t_color) {0,0,0});
// }

// void	hook(void *param)
// {
// 	t_data	*data;
// 	int 			y;
// 	int 			x;
// 	t_ray			light_ray;
// 	t_ray			ray;
// 	t_hit_info		hit_record;
// 	t_hit_info		new_hit;

// 	data = param;
// 	y = 0;
// 	x = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{

// 			ray.origin = data->scene->camera.position;
// 			ray.direction = vec3_matrix_mult(data->scene->camera.m_camera_world,
// 												data->scene->camera.rays[y][x], 1);
// 			hit_record.t = INFINITY;
// 			new_hit.t = INFINITY;
// 			obj_get_nearest(&hit_record, data->scene->objects, ray);
// 			if (!hit_record.object)
// 				put_color_pixel(data, x, y,  (t_color) {0,0,0});	
// 			else if (hit_record.object)
// 			{
// 				light_ray = get_light_ray(hit_record, &ray, data->scene);
// 				obj_get_nearest(&new_hit, data->scene->objects, light_ray);
// 				if(new_hit.object)
// 				{
// 					put_color_pixel(data, x, y, (t_color) {0,0,0});
// 				}
// 				else
// 				{
// 					double nom = vec3_dot(light_ray.direction, hit_record.normal);
// 					double denom = vec3_length(light_ray.direction);
// 					double res =(nom / denom);
// 					put_color_pixel(data, x, y, color_mult_ratio(color_of_object(hit_record.object), res));
// 				}
// 			}
// 			++x;
// 		}
// 		++y;
// 	}
// }

// int	main(int argc, char **argv)
// {
// 	t_data *data;

// 	if (argc != 2 || (argc == 2 && !valid_input(argv[1])))
// 		return (1);
// 	data = malloc(sizeof(t_data));
// 	data->scene = get_scene(argv[1]);
// 	if (!data->scene)
// 	{
// 		printf("GET SCENE UNSUCCESSFULL\n");
// 		free(data);
// 		return (1);
// 	}
// 	print_scene(data->scene);
// 	data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
// 	if (!data->mlx)
// 		exit(EXIT_FAILURE);
// 	data->g_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
// 	memset(data->g_img->pixels, 255, data->g_img->width * data->g_img->height * sizeof(int));
// 	mlx_image_to_window(data->mlx, data->g_img, 0, 0);
// 	mlx_loop_hook(data->mlx, &hook, data);
// 	mlx_loop(data->mlx);
// 	mlx_terminate(data->mlx);
// 	free_scene(data->scene);
// 	free(data);
// 	return (EXIT_SUCCESS);
// }


#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
// #define WIDTH 256
// #define HEIGHT 256

mlx_image_t	*g_img;

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		g_img->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		g_img->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		g_img->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		g_img->instances[0].x += 5;
}

int32_t	main(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, 128, 128);
	memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}