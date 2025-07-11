#include "minirt.h"
#include "ray.h"
#include "objects.h"

// Forward declarations for intersection functions from object files
extern int intersect_sphere(t_ray ray, t_sphere sphere, double *t);
extern int intersect_plane(t_ray ray, t_plane plane, double *t);
extern int intersect_cylinder(t_ray ray, t_cylinder cylinder, double *t);
extern t_vector get_sphere_normal(t_sphere sphere, t_vector point);
extern t_vector get_plane_normal(t_plane plane, t_vector point);
extern t_vector get_cylinder_normal(t_cylinder cylinder, t_vector point);

// Function to create a ray
t_ray create_ray(t_vector origin, t_vector direction)
{
    t_ray ray;

    ray.origin = origin;
    ray.direction = direction;
    return ray;
}

// Helper function to calculate sphere quadratic coefficients
static void calculate_sphere_quadratic(t_ray ray, t_sphere *sphere)
{
    t_vector oc;
    
    oc = vector_subtract(ray.origin, sphere->center);
    sphere->a = vector_dot(ray.direction, ray.direction);
    sphere->b = 2.0 * vector_dot(oc, ray.direction);
    sphere->c = vector_dot(oc, oc) - sphere->radius * sphere->radius;
    sphere->discriminant = sphere->b * sphere->b - 4 * sphere->a * sphere->c;
}

// Helper function to solve sphere intersection
static int solve_sphere_intersection(t_sphere *sphere, double *t)
{
    double t_result;
    
    if (sphere->discriminant < 0)
        return (0);
    t_result = (-sphere->b - sqrt(sphere->discriminant)) / (2.0 * sphere->a);
    if (t_result >= 0)
    {
        *t = t_result;
        return (1);
    }
    return (0);
}

// Function to calculate the intersection of a ray with a sphere
int intersect_ray_sphere(t_ray ray, t_sphere sphere, double *t)
{
    calculate_sphere_quadratic(ray, &sphere);
    return (solve_sphere_intersection(&sphere, t));
}

// Generic function to intersect ray with any object
int intersect_ray_with_object(t_ray ray, t_object *object, double *t)
{
    switch (object->type)
    {
        case SPHERE:
            return (intersect_sphere(ray, object->shape.sphere, t));
        case PLANE:
            return (intersect_plane(ray, object->shape.plane, t));
        case CYLINDER:
            return (intersect_cylinder(ray, object->shape.cylinder, t));
        default:
            return (0);
    }
}

// Function to get normal at intersection point
t_vector get_normal(t_object *object, t_vector point)
{
    switch (object->type)
    {
        case SPHERE:
            return (get_sphere_normal(object->shape.sphere, point));
        case PLANE:
            return (get_plane_normal(object->shape.plane, point));
        case CYLINDER:
            return (get_cylinder_normal(object->shape.cylinder, point));
        default:
            return (create_vector(0, 1, 0));
    }
}