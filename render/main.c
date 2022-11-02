/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:51:48 by mawinter          #+#    #+#             */
/*   Updated: 2022/11/01 18:18:49 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
mlx_image_t	*g_img;

int color = 0;

void	hook(void *param)
{
	t_data	*data;
	int y;
	int x;

	data = param;
	y = 0;
	x = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			x++;
			y++;
		}
	}	
	
	if (WIDTH == 1)
		printf("%f\n", 1.0f / data->mlx->delta_time);
	static int i =0;

	i++;
	if (i == 500)
		mlx_close_window(data->mlx);
}


void	free_data()
{
	return;
}

int	print_scene(t_scene *scene)
{
	int	i;

	i = 0;
	printf("=================Ambient Light==================\n");
	printf("Color: %f %f %f\n", scene->ambient_l.color.r, scene->ambient_l.color.g, scene->ambient_l.color.b);
	printf("Ratio%f\n", scene->ambient_l.ratio);
	printf("=================Camera==================\n");
	printf("Positionj: %f %f %f\n", scene->camera.v_position.x, scene->camera.v_position.y, scene->camera.v_position.z);
	printf("Direction: %f %f %f\n", scene->camera.v_direction.x, scene->camera.v_direction.y, scene->camera.v_direction.z);
	printf("FOV: %d\n", scene->camera.fov);
	print_matrix(scene->camera.m_camera_world);
	printf("-------------------------------------------------\n");
	print_matrix(scene->camera.m_world_camera);
	printf("=================Light==================\n");
	printf("Position: %f %f %f\n", scene->light.position.x, scene->light.position.y, scene->light.position.z);
	printf("Ratio: %f\n", scene->light.brightness_ratio);
	printf("Color: %f %f %f\n", scene->light.color.r, scene->light.color.g, scene->light.color.b);
	printf("=================Sphere==================\n");
	while (scene->spheres[i])
	{
		printf("Position: %f %f %f\n", scene->spheres[i]->position.x, scene->spheres[i]->position.y, scene->spheres[i]->position.z);
		printf("Diameter: %f\n", scene->spheres[i]->diameter);
		printf("Color: %f %f %f\n", scene->spheres[i]->color.r, scene->spheres[i]->color.g, scene->spheres[i]->color.b);
		i++;
	}
	i = 0;
	printf("=================Plane==================\n");
	while (scene->planes[i])
	{
		printf("Position: %f %f %f\n", scene->planes[i]->position.x, scene->planes[i]->position.y, scene->planes[i]->position.z);
		printf("Normal Vec: %f %f %f\n", scene->planes[i]->normal_vec.x, scene->planes[i]->normal_vec.y, scene->planes[i]->normal_vec.z);
		printf("Color: %f %f %f\n", scene->planes[i]->color.r, scene->planes[i]->color.g, scene->planes[i]->color.b);
		i++;
	}
	i = 0;
	printf("=================Cylinders==================\n");
	while (scene->cylinders[i])
	{
		printf("Position: %f %f %f\n", scene->cylinders[i]->position.x, scene->cylinders[i]->position.y, scene->cylinders[i]->position.z);
		printf("Normal Vec: %f %f %f\n", scene->cylinders[i]->normal_vec.x, scene->cylinders[i]->normal_vec.y, scene->cylinders[i]->normal_vec.z);
		printf("Color: %f %f %f\n", scene->cylinders[i]->color.r, scene->cylinders[i]->color.g, scene->cylinders[i]->color.b);
		printf("Diameter: %f\n", scene->cylinders[i]->diameter);
		printf("Height: %f\n", scene->cylinders[i]->height);
		i++;
	}
	printf("================================================\n");
	return (1);
}


int	main(int argc, char **argv)
{
	t_data *data;

	printf("%zu\n", sizeof(t_camera) - (WIDTH * HEIGHT * 3 *sizeof(double)));
	printf("%zu\n", sizeof(t_matrix4x4));
	if (argc == 2 && !valid_input(argv[1]))
		return (1);
	else
		printf("\nValid Input\n");
	data = malloc(sizeof(t_data));
	data->scene = get_scene(argv[1]);
	print_scene(data->scene);
	t_vec3 v;
	v.x = -1;
	v.y = -0.4;
	v.z = 1;
	t_vec3 v2 = vec3_matrix_mult(data->scene->camera.m_camera_world, v, 1);
	t_vec3 v3 = vec3_matrix_mult(data->scene->camera.m_world_camera, v2, 1);
	print_vec3(v);
	print_vec3(v2);
	print_vec3(v3);
	// data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	// if (!data->mlx)
	// 	exit(EXIT_FAILURE);
	// data->g_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	// memset(data->g_img->pixels, 255, data->g_img->width * data->g_img->height * sizeof(int));
	// mlx_image_to_window(data->mlx, data->g_img, 0, 0);
	// mlx_loop_hook(data->mlx, &hook, data);

	// mlx_loop(data->mlx);
	// mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}