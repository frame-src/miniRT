#include "render.h"

static	double cylinder_body_equation(t_cylinder *cylinder, t_ray l_ray)
{
	double	solution[3];
	double	a;
	double	b; 
	double	c;
 
	a = pow(l_ray.direction.x, 2) + pow(l_ray.direction.y, 2);
	b = 2.0L * l_ray.origin.x * l_ray.direction.x +  2.0L * l_ray.origin.y * l_ray.direction.y;
	c = pow(l_ray.origin.x, 2) + pow(l_ray.origin.y, 2) - pow(cylinder->diameter / 2.0L, 2);
	double discriminant = pow(b, 2) - (4 * a * c);
	if (discriminant < 0)
		return (-1.0);
	 // Zmin < Z < Zmax 
	solution[0] = (- b - sqrt(discriminant)) / 2.0 * a;
	solution[1] = (- b + sqrt(discriminant)) / 2.0 * a;
	if(solution[0] > solution[1])
		solution[2] = solution[1];
	else
		solution[2] = solution[0];
	return solution[2];
}
/*
	checking the body of the cylinder; 

*/
static	double cylinder_check_limit(t_cylinder *cylinder, t_ray l_ray, double t)
{
	double		limits;
	t_plane		cap;

	limits = l_ray.origin.z + l_ray.direction.z * t;
	if(limits > l_ray.origin.z - cylinder->height/2 && limits < l_ray.origin.z + cylinder->height/2)
	{
		cap.normal_vec = cylinder->orientation;
		cap.position = (t_vec3){0,0,l_ray.origin.z + cylinder->height/2};
		cap.color = cylinder->color;
		if(get_plane_intersect(&cap, l_ray) != -1)
		{
			t = ((l_ray.origin.z + cylinder->height/2 - cylinder->position.z)/cylinder->orientation.z);
			return (get_plane_intersect(&cap, l_ray));
		}
		cap.position = (t_vec3){0,0,l_ray.origin.z - cylinder->height/2};
		if(get_plane_intersect(&cap, l_ray) != -1)
		{
			t = ((l_ray.origin.z - cylinder->height/2 - cylinder->position.z)/cylinder->orientation.z);
			return (get_plane_intersect(&cap, l_ray));
		}
	}
	return t;
}

double	get_cylinder_intersect(t_cylinder *cylinder, t_ray ray)
{
	t_ray		l_ray;
	double		t;

	l_ray.direction = vec3_matrix_mult(cylinder->m_to_cylinder, ray.direction, 1);
	l_ray.origin = vec3_matrix_mult(cylinder->m_to_cylinder, ray.origin, 0);
	t = cylinder_body_equation(cylinder, l_ray);
	if(t == -1)
		return(t);
	else
		t = cylinder_check_limit(cylinder, l_ray, t);
	return t;
}