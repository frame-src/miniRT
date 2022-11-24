
t_object *object_return_nearest(t_object *list, t_ray *ray, double *t)
{
	iterate through the list
	if(call object_get_intersection
	and return the index of the nearest one;
}

object_get_intersection(t_object *list,)

t_color	*object_get_color(double *t, t_object *object, t_ray *ray)
{
	t_point *point;

	point = point_calculate( t, ray);

	if(object.type == spehere)
		spehere_get_color()...
	if(...)
		..._get_color()...
	...

}