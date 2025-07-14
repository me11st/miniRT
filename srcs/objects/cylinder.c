#include "minirt.h"
#include "objects.h"
#include "vector.h"
#include "ray.h"
#include "color.h"
#include <math.h>

t_object create_cylinder(t_cylinder cylnd)
{
    t_object obj;
    
    obj.type = CYLINDER;
    obj.shape.cylinder = cylnd;
    obj.shape.cylinder.direction = vector_normalize(cylnd.direction);
    return (obj);
}

// Helper function to calculate quadratic coefficients for cylinder intersection
static void calculate_cylinder_quadratic(t_ray ray, t_cylinder *cylinder)
{
    t_vector    oc;
    double      ray_dot_axis;
    double      oc_dot_axis;
    t_vector    ray_perp;
    t_vector    oc_perp;

    // Calculate vector from ray origin to cylinder center
    oc = vector_subtract(ray.origin, cylinder->center);
    // Project ray direction and oc onto plane perpendicular to cylinder axis
    ray_dot_axis = vector_dot(ray.direction, cylinder->direction);
    oc_dot_axis = vector_dot(oc, cylinder->direction);
    ray_perp = vector_subtract(ray.direction, vector_scale(cylinder->direction, ray_dot_axis));
    oc_perp = vector_subtract(oc, vector_scale(cylinder->direction, oc_dot_axis));
    // Calculate quadratic coefficients and store in struct
    cylinder->a = vector_dot(ray_perp, ray_perp);
    cylinder->b = 2.0 * vector_dot(oc_perp, ray_perp);
    cylinder->c = vector_dot(oc_perp, oc_perp) - cylinder->radius * cylinder->radius;
}

// Helper function to solve quadratic and find valid intersection
static int solve_cylinder_intersection(t_cylinder *cylinder, double *t)
{
    double  discriminant;
    double  t1;
    double  t2;
    double  hit_t;

    discriminant = cylinder->b * cylinder->b - 4 * cylinder->a * cylinder->c;
    if (discriminant < 0)
        return 0;
    t1 = (-cylinder->b - sqrt(discriminant)) / (2.0 * cylinder->a);
    t2 = (-cylinder->b + sqrt(discriminant)) / (2.0 * cylinder->a);
    // Choose the closest positive intersection
    hit_t = (t1 > 0.001) ? t1 : t2;
    if (hit_t <= 0.001)
        return 0;
    *t = hit_t;
    return 1;
}

// Helper function to check if intersection point is within cylinder height bounds
static int check_cylinder_height_bounds(t_ray ray, t_cylinder *cylinder, double t)
{
    t_vector    hit_point;
    t_vector    hit_to_center;
    double      height_projection;
    
    hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
    hit_to_center = vector_subtract(hit_point, cylinder->center);
    height_projection = vector_dot(hit_to_center, cylinder->direction);
    return (height_projection >= 0 && height_projection <= cylinder->height);
}

// Function to check intersection of a ray with a cylinder
int intersect_cylinder(t_ray ray, t_cylinder cylinder, double *t) 
{
    double temp_t;
    
    // Calculate quadratic equation coefficients
    calculate_cylinder_quadratic(ray, &cylinder);
    // Solve for intersection
    if (!solve_cylinder_intersection(&cylinder, &temp_t))
        return 0;
    // Check height bounds
    if (!check_cylinder_height_bounds(ray, &cylinder, temp_t))
        return 0;
    *t = temp_t;
    return 1;
}

// Function to calculate the normal at a point on the cylinder's surface
t_vector get_cylinder_normal(t_cylinder cylinder, t_vector point) 
{
    t_vector    point_to_center;
    double      projection;
    t_vector    projected_point;

    point_to_center = vector_subtract(point, cylinder.center);
    projection = vector_dot(point_to_center, cylinder.direction);
    projected_point = vector_add(cylinder.center, vector_scale(cylinder.direction, projection));
    return (vector_normalize(vector_subtract(point, projected_point)));
}