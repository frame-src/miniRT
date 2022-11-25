#include "../objects/objects.h"

// t = (l0 - p0)* n/1*n = 
double	plane_get_intersection( t_plane *plane, t_ray *ray)
{
	//are the value already normalized?
	double	denom;
	double	nom;
	t_vec3	tmp;

	denom = vec3_dot(plane.normal_vec, ray->direction);
	if (denom > 0)
	{
		tmp = vec3_sub(plane->position, ray->origin);
		nom = vec3_dot(tmp, plane->normal_vec);
		return (nom / denom);
	}
	else
		return (-1);
}

color_get_intersection

t_ray	*ray_cast_inter_to_light(double t, t_ray	*ray,)
{
	origin_set()
}