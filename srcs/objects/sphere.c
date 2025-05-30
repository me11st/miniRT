#include "minirt.h"
#include "objects.h"
#include "vector.h"
#include "ray.h"

t_sphere create_sphere(t_vector center, double radius)
{
    t_sphere sphere;

    sphere.center = center;
    sphere.radius = radius;
    return sphere;
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

    *t = (-b - sqrt(discriminant)) / (2.0 * a);
    if (*t < 0)
        *t = (-b + sqrt(discriminant)) / (2.0 * a);
    
    return (*t >= 0);
}

t_vector get_sphere_normal(t_sphere sphere, t_vector point)
{
    return vector_normalize(vector_subtract(point, sphere.center));
}