/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:11:08 by mawinter          #+#    #+#             */
/*   Updated: 2022/12/13 11:57:34 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

void	print_ray(t_ray ray)
{
	printf("====================== Ray ========================\n");
	printf("origin:    ");
	print_vec3(ray.origin);
	printf("direction: ");
	print_vec3(ray.direction);
}

int	print_scene(t_scene *scene)
{
	printf("================= Ambient Light ==================\n");
	printf("Color:      %d %d %d\n", scene->ambient_l.color.r, scene->ambient_l.color.g, scene->ambient_l.color.b);
	printf("Ratio:      %f\n", scene->ambient_l.ratio);
	printf("================= Camera =========================\n");
	printf("Position:   %f %f %f\n", scene->camera.position.x, scene->camera.position.y, scene->camera.position.z);
	printf("Direction:  %f %f %f\n", scene->camera.direction.x, scene->camera.direction.y, scene->camera.direction.z);
	printf("FOV:        %d\n", scene->camera.fov);
	printf("---------------------to world---------------------\n");
	print_matrix(scene->camera.m_camera_world);
	printf("---------------------to cam---------------------\n");
	print_matrix(scene->camera.m_world_camera);
	printf("================= Light ==========================\n");
	printf("Position:   %f %f %f\n", scene->light.position.x, scene->light.position.y, scene->light.position.z);
	printf("Ratio:      %f\n", scene->light.brightness_ratio);
	printf("Color:      %d %d %d\n", scene->light.color.r, scene->light.color.g, scene->light.color.b);
	t_object *head = scene->objects;
	while (head)
	{
		if (head->type == 's')
		{
			printf("================= Sphere =========================\n");
			printf("Position:   %f %f %f\n", head->sphere->position.x, head->sphere->position.y, head->sphere->position.z);
			printf("Radius:   %f\n", head->sphere->radius);
			printf("Color:      %d %d %d\n", head->sphere->color.r, head->sphere->color.g, head->sphere->color.b);	
		}
		if (head->type == 'p')
		{
			printf("================= Plane ==========================\n");
			printf("Position:   %f %f %f\n", head->plane->position.x, head->plane->position.y, head->plane->position.z);
			printf("Normal Vec: %f %f %f\n", head->plane->normal_vec.x, head->plane->normal_vec.y, head->plane->normal_vec.z);
			printf("Color:      %d %d %d\n", head->plane->color.r, head->plane->color.g, head->plane->color.b);	
		}
		if (head->type == 'c')
		{
			printf("================= Cylinders ======================\n");
			printf("Position:   %f %f %f\n", head->cylinder->position.x, head->cylinder->position.y, head->cylinder->position.z);
			printf("Normal Vec: %f %f %f\n", head->cylinder->orientation.x, head->cylinder->orientation.y, head->cylinder->orientation.z);
			printf("Color:      %d %d %d\n", head->cylinder->color.r, head->cylinder->color.g, head->cylinder->color.b);
			printf("Diameter:   %f\n", head->cylinder->diameter);
			printf("Height:     %f\n", head->cylinder->height);
			printf("--------------------to world----------------------\n");
			print_matrix(head->cylinder->m_to_world);
			printf("---------------------to cyl-----------------------\n");
			print_matrix(head->cylinder->m_to_cylinder);
		}
		head = head->next;
	}
	printf("================================================\n");
	return (1);
}
