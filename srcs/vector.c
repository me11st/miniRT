#include "vector.h"
#include <math.h>

t_vector vec_add(t_vector a, t_vector b)
{
    return (t_vector){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vector vec_sub(t_vector a, t_vector b)
{
    return (t_vector){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_vector vec_scale(t_vector v, double scalar)
{
    return (t_vector){v.x * scalar, v.y * scalar, v.z * scalar};
}

double vec_dot(t_vector a, t_vector b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector vec_cross(t_vector a, t_vector b)
{
    return (t_vector){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

double vec_length(t_vector v)
{
    return sqrt(vec_dot(v, v));
}

t_vector vec_normalize(t_vector v)
{
    double length = vec_length(v);
    if (length == 0)
        return (t_vector){0, 0, 0}; // Handle zero-length vector
    return vec_scale(v, 1.0 / length);
}