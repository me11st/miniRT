#include "minirt.h"
#include "objects.h"

// Function to calculate the intersection of a ray with a plane
int intersect_plane(t_ray *ray, t_plane *plane, double *t)
{
    double denom;
    double numerator;

    denom = dot_product(plane->normal, ray->direction);
    if (fabs(denom) > 1e-6)
    {
        numerator = dot_product(plane->point, plane->normal) - dot_product(ray->origin, plane->normal);
        *t = numerator / denom;
        return (*t >= 0);
    }
    return 0;
}

// Function to calculate the normal of a plane at a given point
t_vector get_plane_normal(t_plane *plane, t_vector point)
{
    return plane->normal; // Normal is constant for a plane
}

// Function to create a plane object
t_plane create_plane(t_vector point, t_vector normal)
{
    t_plane plane;

    plane.point = point;
    plane.normal = normalize(normal);
    return plane;
}