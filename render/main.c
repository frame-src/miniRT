/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:51:48 by mawinter          #+#    #+#             */
/*   Updated: 2022/11/25 16:55:45 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double get_sphere_intersect(t_ray ray, t_sphere *cur_sphere)
{
	t_vec3 oc = vec3_sub(ray.origin, cur_sphere->position);
	double A = 1.0f;
	double B = 2.0 * vec3_dot(oc, ray.direction);
	double C = vec3_dot(oc, oc) - (cur_sphere->radius)*(cur_sphere->radius);
	double discriminant = B*B - 4*A*C;
	if(discriminant < 0)
		return (-1.0);
	return (-B - sqrt(discriminant)) / (2.0*A);
}

void	put_color_pixel(t_data *data, int x, int y, t_color color)
{
	mlx_put_pixel(data->g_img, x, y, color.r << 24 | color.g << 16 | color.b << 8 | 255);
}



// t_color	calc_pixel_color(t_scene *scene)
// {
// 	double	t1;
// 	double	t2;
// 	double	t3;

// 	t1 = 0.0L;
// 	t2 = 0.0L;
// 	t3 = 0.0L;
// 	t1 = get_nearest_sphere();
// 	t2 = get_nearest_plane();
// 	t3 = get_nearest_cylinder();
// 	if (t1 != -1.0L && t1 <= t2 && t2 <= t3)
// 		;
// 	else if (t2 != -1.0L && t2 <= t3 && t3 <= t1)
// 		;
// 	else if (t3 != -1.0L && t3 <= t2 && t2 <= t1)
// 		;
// 	else
// 		printf("I Should Never Be Here\n");
	
// }

// void	render(t_data *data)
// {
// 	int		x;
// 	int		y;
// 	// t_ray	ray; 
// 	// t_color	pixel_color;

// 	x = 0;
// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		while (x < WIDTH)
// 		{
// 			// ray.direction = vec3_matrix_mult(data->scene->camera.m_camera_world,
// 			// 		data->scene->camera.rays[y][x], 1);
// 			// ray.origin = data->scene->camera.v_position;
// 			// pixel_color = calc_pixel_color(data->scene);
// 			// put_color_pixel(data, x, y, pixel_color);
		
// 		}
// 	}
// }


void	hook(void *param)
{
	t_data	*data;
	data= NULL;
	if(data)
		data = NULL;
	int 	y;
	int 	x;
	t_color	color;

	color.r = 0; color.g = 0; color.b = 255;
	data = param;
	y = 0;
	x = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			// t_ray ray;
			// ray.direction = vec3_matrix_mult(data->scene->camera.m_camera_world, data->scene->camera.rays[y][x], 1);
	
			x++;
		}
		y++;
	}
	// printf("%f\n", 1 / data->mlx->delta_time);
}


void	free_data()
{
	return;
}

int	print_scene(t_scene *scene)
{
	printf("=================Ambient Light==================\n");
	printf("Color: %d %d %d\n", scene->ambient_l.color.r, scene->ambient_l.color.g, scene->ambient_l.color.b);
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
	printf("Color: %d %d %d\n", scene->light.color.r, scene->light.color.g, scene->light.color.b);
	t_object *head = scene->objects;
	while (head)
	{
		if (head->type == 's')
		{
			printf("=================Sphere==================\n");
			printf("Position: %f %f %f\n", head->sphere->position.x, head->sphere->position.y, head->sphere->position.z);
			printf("Diameter: %f\n", head->sphere->radius);
			printf("Color: %d %d %d\n", head->sphere->color.r, head->sphere->color.g, head->sphere->color.b);	
		}
		if (head->type == 'p')
		{
			printf("=================Plane==================\n");
			printf("Position: %f %f %f\n", head->plane->position.x, head->plane->position.y, head->plane->position.z);
			printf("Normal Vec: %f %f %f\n", head->plane->normal_vec.x, head->plane->normal_vec.y, head->plane->normal_vec.z);
			printf("Color: %d %d %d\n", head->plane->color.r, head->plane->color.g, head->plane->color.b);	
		}
		if (head->type == 'c')
		{
			printf("=================Cylinders==================\n");
			printf("Position: %f %f %f\n", head->cylinder->position.x, head->cylinder->position.y, head->cylinder->position.z);
			printf("Normal Vec: %f %f %f\n", head->cylinder->orientation.x, head->cylinder->orientation.y, head->cylinder->orientation.z);
			printf("Color: %d %d %d\n", head->cylinder->color.r, head->cylinder->color.g, head->cylinder->color.b);
			printf("Diameter: %f\n", head->cylinder->diameter);
			printf("Height: %f\n", head->cylinder->height);
		}
		head = head->next;
	}
	printf("================================================\n");
	return (1);
}


int	main(int argc, char **argv)
{
	t_data *data;

	if (argc != 2)
		return (1);
	printf("%zu\n", sizeof(t_camera) - (WIDTH * HEIGHT * 3 *sizeof(double)));
	printf("%zu\n", sizeof(t_matrix4x4));
	if (argc == 2 && !valid_input(argv[1]))
		return (1);
	else
		printf("\nValid Input\n");
	data = malloc(sizeof(t_data));
	data->scene = get_scene(argv[1]);

	printf("GET SCENE SUCCESSFULL");
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
	data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	if (!data->mlx)
		exit(EXIT_FAILURE);
	data->g_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	memset(data->g_img->pixels, 255, data->g_img->width * data->g_img->height * sizeof(int));
	mlx_image_to_window(data->mlx, data->g_img, 0, 0);
	mlx_loop_hook(data->mlx, &hook, data);
	//hook(data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}