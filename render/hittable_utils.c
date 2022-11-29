#include "render.h"

// bool	set_front_face(t_hit_record *hit, t_ray ray, t_vec3 norm)
// {
// 	double direction;

// 	direction = vec3_dot(ray.direction, norm);
// 	if(direction > 0)
// 	{
// 		bool = false;
// 		direction = ;
// 	}
// }

void norm_set_hit_record(t_hit_info **hit_record, t_ray ray, t_vec3 norm)
{
	double direction;
	vec3_normalize(&norm);
	(*hit_record)->normal = norm;
	direction = vec3_dot(ray.direction, norm);
	if(direction < 0)
		return ;
	else
		(*hit_record)->normal = vec3_mult(-1, norm);
}
