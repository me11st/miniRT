#ifndef OBJECTS_H
#define OBJECTS_H

#include "vector.h"
#include "color.h"
#include "ray.h"

typedef struct s_sphere {
    double radius;
    t_vector center;
    t_color color;
} t_sphere;

typedef struct s_cylinder {
    double radius;
    double height;
    t_vector center;
    t_vector direction;
    t_color color;
} t_cylinder;

typedef struct s_plane {
    t_vector point;
    t_vector normal;
    t_color color;
} t_plane;

typedef enum e_object_type {
    SPHERE = 0,
    CYLINDER = 1,
    PLANE = 2
} t_object_type;

typedef struct s_object {
    t_object_type type;
    union {
        t_sphere sphere;
        t_cylinder cylinder;
        t_plane plane;
    } shape;
} t_object;

// Object creation functions
t_object create_sphere(t_vector center, double radius, t_color color);
t_object create_cylinder(t_cylinder cylnd);
t_object create_plane(t_vector point, t_vector normal, t_color color);

// Intersection functions
int intersect_ray_with_object(t_ray ray, t_object *object, double *t);
t_vector get_normal(t_object *object, t_vector point);

#endif // OBJECTS_H