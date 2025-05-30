#ifndef RAY_H
#define RAY_H

typedef struct s_ray {
    t_vector origin;  // The starting point of the ray
    t_vector direction; // The direction in which the ray is pointing
} t_ray;

t_ray create_ray(t_vector origin, t_vector direction);
int intersect_sphere(t_ray ray, t_sphere sphere, double *t);
int intersect_plane(t_ray ray, t_plane plane, double *t);
int intersect_cylinder(t_ray ray, t_cylinder cylinder, double *t);

#endif // RAY_H