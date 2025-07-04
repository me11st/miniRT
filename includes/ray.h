#ifndef RAY_H
#define RAY_H

#include "vector.h"

typedef struct s_ray {
    t_vector origin;    // The starting point of the ray
    t_vector direction; // The direction in which the ray is pointing
} t_ray;

// Basic ray functions
t_ray create_ray(t_vector origin, t_vector direction);

#endif // RAY_H