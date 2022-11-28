#include "render.h"
/*
	checking the body of the cylinder; 

*/
static	double cylinder_check_limit(t_cylinder *cylinder, t_ray l_ray, double t)
{
	double		limits;

	limits = l_ray.origin.z + l_ray.direction.z * t;
	if(limits <= cylinder->height/2 && limits >=  -1 * cylinder->height/2)
		return (t);
	return -1.0L;
}

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
		return (-1.0L);
	 // Zmin < Z < Zmax 
	solution[0] = (- b - sqrt(discriminant)) / (2.0 * a);
	solution[1] = (- b + sqrt(discriminant)) / (2.0 * a);
	if (solution[0] < 0.0L)
		solution[2] = solution[1];
	else
		solution[2] = solution[0];
	return (cylinder_check_limit(cylinder, l_ray, solution[2]));
}


double	get_disk_intersect(t_plane *plane, t_ray ray, double radius)
{
	double	t;
	double	dist;
	t_vec3	hitpoint;
	t_vec3	distancevector;

	t = get_plane_intersect(plane, ray);
	if (t == -1.0L)
		return (-1.0L);
	hitpoint = vec3_add(ray.origin, vec3_mult(t, ray.direction));
	distancevector = vec3_sub(plane->position, hitpoint);
	dist = vec3_length(distancevector);
	if (dist <= radius)
	{

		return (t);
	}
	else
		return (-1.0L);
}

double	get_cylinder_intersect(t_cylinder *cylinder, t_ray ray)
{
	t_ray		l_ray;
	double		t1;
	double		t2;
	double		t3;
	t_plane		top_cap;
	t_plane		bottom_cap;

	l_ray.direction = vec3_matrix_mult(cylinder->m_to_cylinder, ray.direction, 1);
	l_ray.origin = vec3_matrix_mult(cylinder->m_to_cylinder, ray.origin, 0);
	top_cap.normal_vec = cylinder->position;
	top_cap.position = (t_vec3) {0, 0, cylinder->height / 2};
	bottom_cap.normal_vec = cylinder->position;
	bottom_cap.position = (t_vec3) {0, 0, -cylinder->height / 2};
	t1 = get_disk_intersect(&top_cap, l_ray, cylinder->diameter / 2.0L);
	t2 = get_disk_intersect(&bottom_cap, l_ray, cylinder->diameter / 2.0L);
	t3 = cylinder_body_equation(cylinder, l_ray);
	if (t1 >= 0 && (t2 == -1.0L || t1 <= t2) && (t3 == -1.0L || t1 <= t3))
	{
		return (t1);
	}
	if (t2 >= 0 && (t3 == -1.0L || t1 <= t3) && (t1 == -1.0L || t2 <= t1))
	{
		return (t2);
	}
	else if (t3 >= 0)
	{
		return (t3);
	}
	return (-1.0L);
}