/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:51:48 by mawinter          #+#    #+#             */
/*   Updated: 2022/11/01 00:29:18 by marius           ###   ########.fr       */
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
		break;
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


int	main(int argc, char **argv)
{
	t_data *data;

	if (argc == 2 && !valid_input(argv[1]))
		return (1);
	else
		printf("\nValid Input\n");
	data = malloc(sizeof(t_data));
	data->scene = get_scene(argv[1]);
	printf("Ambient Color:\n");
	printf("%f\n", data->scene->ambient_l.color.r);
	printf("%f\n", data->scene->ambient_l.color.g);
	printf("%f\n", data->scene->ambient_l.color.b);
	printf("Ambient Ratio%f\n", data->scene->ambient_l.ratio);
	printf("Camer:\n");
	printf("%f\n", data->scene->camera.v_direction.x);
	printf("%f\n", data->scene->camera.v_direction.y);
	printf("%f\n", data->scene->camera.v_direction.z);
	printf("%f\n", data->scene->camera.v_position.x);
	printf("%f\n", data->scene->camera.v_position.y);
	printf("%f\n", data->scene->camera.v_position.z);
	printf("%d\n", data->scene->camera.fov);

		printf("sphere:\n");
	printf("%f\n", data->scene->spheres[0]->color.r);
	printf("%f\n", data->scene->spheres[0]->color.g);
	printf("%f\n", data->scene->spheres[0]->color.b);
	printf("%f\n", data->scene->spheres[0]->diameter);
	printf("%f\n", data->scene->spheres[0]->position.x);
	printf("%f\n", data->scene->spheres[0]->position.y);
	printf("%f\n", data->scene->spheres[0]->position.z);
	printf("%d\n", data->scene->camera.fov);
	
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