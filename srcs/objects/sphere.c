#include "minirt.h"
#include "objects.h"
#include "vector.h"
#include "ray.h"
#include "color.h"
#include <math.h>

t_object create_sphere(t_vector center, double radius, t_color color)
{
    t_object obj;
    
    obj.type = SPHERE;
    obj.shape.sphere.center = center;
    obj.shape.sphere.radius = radius;
    obj.shape.sphere.color = color;
    return obj;
}

int intersect_sphere(t_ray ray, t_sphere sphere, double *t)
{
    t_vector oc = vector_subtract(ray.origin, sphere.center);
    double a = vector_dot(ray.direction, ray.direction);
    double b = 2.0 * vector_dot(oc, ray.direction);
    double c = vector_dot(oc, oc) - sphere.radius * sphere.radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return 0;

    double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
    
    // Return the closest positive intersection
    if (t1 > 0.001)
        *t = t1;
    else if (t2 > 0.001)
        *t = t2;
    else
        return 0;
    
    return 1;
}

t_vector get_sphere_normal(t_sphere sphere, t_vector point)
{
    return vector_normalize(vector_subtract(point, sphere.center));
}