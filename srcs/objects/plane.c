#include "minirt.h"
#include "objects.h"
#include "vector.h"
#include "ray.h"
#include "color.h"
#include <math.h>

t_object create_plane(t_vector point, t_vector normal, t_color color)
{
    t_object	obj;
    
    obj.type = PLANE;
    obj.shape.plane.point = point;
    obj.shape.plane.normal = vector_normalize(normal);
    obj.shape.plane.color = color;
    return (obj);
}

// Function to calculate the intersection of a ray with a plane
int intersect_plane(t_ray ray, t_plane plane, double *t)
{
    double      denom;
    double      numerator;
    t_vector    plane_to_origin;

    denom = vector_dot(plane.normal, ray.direction);
    if (fabs(denom) > 1e-6)
    {
        plane_to_origin = vector_subtract(plane.point, ray.origin);
        numerator = vector_dot(plane_to_origin, plane.normal);
        *t = numerator / denom;
        return (*t > 0.001);
    }
    return 0;
}

// Function to calculate the normal of a plane at a given point
t_vector get_plane_normal(t_plane plane, t_vector point)
{
    (void)point;
    return (plane.normal);
}