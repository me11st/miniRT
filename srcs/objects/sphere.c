#include "minirt.h"
#include "objects.h"
#include "vector.h"
#include "ray.h"
#include "color.h"
#include <math.h>

t_object create_sphere(t_vector center, double radius, t_color color)
{
    t_object	obj;
    
    obj.type = SPHERE;
    obj.shape.sphere.center = center;
    obj.shape.sphere.radius = radius;
    obj.shape.sphere.color = color;
    return (obj);
}

int intersect_sphere(t_ray ray, t_sphere sphere, double *t)
{
    t_vector	oc;
    double		a;
    double		b;
    double		c;
    double		discriminant;

    oc = vector_subtract(ray.origin, sphere.center);
	a = vector_dot(ray.direction, ray.direction);
	b = 2.0 * vector_dot(oc, ray.direction);
	c = vector_dot(oc, oc) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
        return (0);
    if ((-b - sqrt(discriminant)) / (2.0 * a) > 0.001)
        *t = (-b - sqrt(discriminant)) / (2.0 * a);
    else if ((-b + sqrt(discriminant)) / (2.0 * a) > 0.001)
        *t = (-b + sqrt(discriminant)) / (2.0 * a);
    else
        return (0);
    return (1);
}

t_vector get_sphere_normal(t_sphere sphere, t_vector point)
{
    return (vector_normalize(vector_subtract(point, sphere.center)));
}