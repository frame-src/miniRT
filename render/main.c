/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:51:48 by mawinter          #+#    #+#             */
/*   Updated: 2023/01/24 15:58:25 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>

#include "../minirt.h"

int	error_scene(t_data *data)
{
	printf("GET SCENE UNSUCCESSFULL\n");
	free(data);
	return (1);
}

static void	esc_key_pressing(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == 256)
	{
		mlx_terminate(data->mlx);
		free_scene(data->scene);
		free(data);
		exit(EXIT_SUCCESS);
	}
}

/*
void leaks (void)
{
	system("leaks miniRT");
}
	atexit(leaks);
*/

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2 || (argc == 2 && !valid_input(argv[1])))
		return (1);
	data = malloc(sizeof(t_data));
	data->scene = get_scene(argv[1]);
	if (!data->scene)
		return (error_scene(data));
	data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	if (!data->mlx)
		exit(EXIT_FAILURE);
	data->g_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	memset(data->g_img->pixels, 255,
		data->g_img->width * data->g_img->height * sizeof(int));
	mlx_image_to_window(data->mlx, data->g_img, 0, 0);
	mlx_loop_hook(data->mlx, &hook, data);
	mlx_key_hook(data->mlx, esc_key_pressing, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	free_scene(data->scene);
	free(data);
	return (EXIT_SUCCESS);
}
