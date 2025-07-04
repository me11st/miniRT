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
    return obj;
}

// Function to check intersection of a ray with a cylinder
int intersect_cylinder(t_ray ray, t_cylinder cylinder, double *t) 
{
    // For now, let's implement a simple infinite cylinder intersection
    // A full cylinder with caps is more complex
    
    t_vector oc = vector_subtract(ray.origin, cylinder.center);
    t_vector axis = cylinder.direction;
    
    // Project ray direction and oc onto plane perpendicular to cylinder axis
    double ray_dot_axis = vector_dot(ray.direction, axis);
    double oc_dot_axis = vector_dot(oc, axis);
    
    t_vector ray_perp = vector_subtract(ray.direction, vector_scale(axis, ray_dot_axis));
    t_vector oc_perp = vector_subtract(oc, vector_scale(axis, oc_dot_axis));
    
    // Solve quadratic equation
    double a = vector_dot(ray_perp, ray_perp);
    double b = 2.0 * vector_dot(oc_perp, ray_perp);
    double c = vector_dot(oc_perp, oc_perp) - cylinder.radius * cylinder.radius;
    
    double discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0)
        return 0;
    
    double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
    
    // Check which intersection is valid and within height bounds
    double hit_t = (t1 > 0.001) ? t1 : t2;
    if (hit_t <= 0.001)
        return 0;
    
    // Check if intersection is within cylinder height
    t_vector hit_point = vector_add(ray.origin, vector_scale(ray.direction, hit_t));
    t_vector hit_to_center = vector_subtract(hit_point, cylinder.center);
    double height_projection = vector_dot(hit_to_center, axis);
    
    if (height_projection < 0 || height_projection > cylinder.height)
        return 0;
    
    *t = hit_t;
    return 1;
}

// Function to calculate the normal at a point on the cylinder's surface
t_vector get_cylinder_normal(t_cylinder cylinder, t_vector point) 
{
    t_vector point_to_center = vector_subtract(point, cylinder.center);
    double projection = vector_dot(point_to_center, cylinder.direction);
    t_vector projected_point = vector_add(cylinder.center, vector_scale(cylinder.direction, projection));
    return vector_normalize(vector_subtract(point, projected_point));
}