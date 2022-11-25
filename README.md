November 25 2022

>	added plane intersection:
	int teory 
		if the direction of the ray and the normal vector are parallel the dot product is zero; and they will never match;
		else if they have a solution that is given by the common point so:
		(p - p0) dot n = 0
		l0 + l*t = p;

		that solved in t give us:
		t = [(p0 - l0) dot n ]/[l dot n]; 
``` c

double plane_intersection(t_plane, t_ray);
``` 

November 24 2022


``` c
t_object *object_return_nearest(t_object *list, t_ray *ray, double *t)
{
	iterate through the list
	if(call object_get_intersection
	and return the index of the nearest one;
}
```

object_get_intersection(t_object *list,)

``` c
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
```
