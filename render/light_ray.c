#include "../objects/objects.h"
#include "render.h"

// t_ray	*shadowray_cast(double t, t_ray	*ray, t_light *light)
// {
// 	origin_set();
// }

t_ray	get_light_ray(double t, t_ray *ray, t_scene *scene, t_object *cur_obj)
{
	t_vec3 surfacenormal;
	t_vec3 hitpoint;
	t_ray light_ray;

	hitpoint = vec3_add(ray->origin, vec3_mult(t, ray->direction));
	surfacenormal = get_surface_normal(cur_obj, hitpoint, &scene->light);
	hitpoint = move_by_vec_ratio(hitpoint, EPSILON, surfacenormal);

	light_ray.origin = hitpoint;
	light_ray.direction = vec3_sub(scene->light.position, hitpoint);
	vec3_normalize(&light_ray.direction);
	return (light_ray);
}