#include "minirt.h"
#include "objects.h"
#include "vector.h"
#include "ray.h"

// Structure representing a cylinder
typedef struct s_cylinder {
    t_vector position; // Position of the cylinder's base
    t_vector direction; // Direction vector of the cylinder
    double radius; // Radius of the cylinder
    double height; // Height of the cylinder
} t_cylinder;

// Function to create a new cylinder
t_cylinder create_cylinder(t_vector position, t_vector direction, double radius, double height) {
    t_cylinder cylinder;

    cylinder.position = position;
    cylinder.direction = normalize(direction); // Ensure direction is normalized
    cylinder.radius = radius;
    cylinder.height = height;

    return cylinder;
}

// Function to check intersection of a ray with a cylinder
int intersect_cylinder(t_ray *ray, t_cylinder *cylinder, double *t) {
    // Implementation of ray-cylinder intersection logic
    // This will involve solving the quadratic equation derived from the cylinder's equation
    // and checking if the intersection point lies within the height of the cylinder.

    // Placeholder for intersection logic
    return 0; // Return 1 if intersection occurs, 0 otherwise
}

// Function to calculate the normal at a point on the cylinder's surface
t_vector normal_at_cylinder(t_cylinder *cylinder, t_vector point) {
    // Implementation to calculate the normal vector at the given point on the cylinder's surface

    // Placeholder for normal calculation logic
    return (t_vector){0, 0, 0}; // Return the normal vector
}