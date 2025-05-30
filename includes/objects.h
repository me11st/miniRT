#ifndef OBJECTS_H
#define OBJECTS_H


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

typedef struct s_object {
    int type; // 0 for sphere, 1 for cylinder, 2 for plane
    union {
        t_sphere sphere;
        t_cylinder cylinder;
        t_plane plane;
    } shape;
} t_object;

t_object *create_sphere(t_vector center, double radius, t_color color);
t_object *create_cylinder(t_vector center, double radius, double height, t_vector direction, t_color color);
t_object *create_plane(t_vector point, t_vector normal, t_color color);
int intersect_ray_with_object(t_ray ray, t_object *object, double *t);
t_vector get_normal(t_object *object, t_vector point);

#endif // OBJECTS_H