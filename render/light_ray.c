#include "../objects/objects.h"

// t_ray	*shadowray_cast(double t, t_ray	*ray, t_light *light)
// {
// 	origin_set();
// }

t_ray	get_light_ray(double t, t_ray *ray, t_scene *scene)
{
	t_ray	light_ray;

	light_ray.origin = vec3_add(ray->origin, vec3_mult(t, ray->direction));
	light_ray.direction = vec3_sub(scene->light.position, light_ray.origin);
	vec3_normalize(&light_ray.direction);
	return (light_ray);
}