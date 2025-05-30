#include "minirt.h"
#include "ray.h"
#include "objects.h"

// Function to create a ray
t_ray create_ray(t_vector origin, t_vector direction)
{
    t_ray ray;

    ray.origin = origin;
    ray.direction = direction;
    return ray;
}

// Function to calculate the intersection of a ray with a sphere
int intersect_ray_sphere(t_ray ray, t_sphere sphere, double *t)
{
    t_vector oc = vector_subtract(ray.origin, sphere.center);
    double a = vector_dot(ray.direction, ray.direction);
    double b = 2.0 * vector_dot(oc, ray.direction);
    double c = vector_dot(oc, oc) - sphere.radius * sphere.radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return 0;

    *t = (-b - sqrt(discriminant)) / (2.0 * a);
    return (*t >= 0);
}

// Function to calculate the intersection of a ray with a cylinder
int intersect_ray_cylinder(t_ray ray, t_cylinder cylinder, double *t)
{
    // Implementation for cylinder intersection
    // This will involve similar calculations as the sphere intersection
    // Placeholder for now
    return 0;
}

// Function to calculate the intersection of a ray with a plane
int intersect_ray_plane(t_ray ray, t_plane plane, double *t)
{
    // Implementation for plane intersection
    // Placeholder for now
    return 0;
}