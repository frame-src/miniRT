#ifndef VECMATH_H
# define VECMATH_H
# define EPSILON 0.00001
#include <math.h>

typedef struct s_matrix4x4
{
	double	m[16];
}	t_matrix4x4;

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct  s_vec4
{
	double	x;
	double	y;
	double	z;
	double	t;
}				t_vec4;

double	vec3_length(t_vec3 v);
double	vec3_dot(t_vec3 v0, t_vec3 v1);
void	vec3_normalize(t_vec3 *v);
t_vec3	vec3_cross(t_vec3 v0, t_vec3 v1);
t_vec3	vec3_add(t_vec3 v0, t_vec3 v1);
t_vec3	vec3_sub(t_vec3 v0, t_vec3 v1);
t_vec3	vec3_mult(double t, t_vec3 v);
t_vec3	vec3_div(double t, t_vec3 v);
void	vec3_set(t_vec3 *v, double x, double y, double z);
int		vec3_is_equal(t_vec3 v0, t_vec3 v1);
int		vec3_is_nearly_equal(t_vec3 v0, t_vec3 v1);
t_vec3	vec3_matrix_mult(t_matrix4x4 m, t_vec3 v, int is_dir);
void	print_matrix(t_matrix4x4 m);
void	print_vec3(t_vec3 v);
int		invert_matrix(const double m[16], double invOut[16]);
#endif