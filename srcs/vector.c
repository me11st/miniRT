#include "vector.h"
#include <math.h>

t_vector create_vector(double x, double y, double z)
{
    return (t_vector){x, y, z};
}

t_vector vector_add(t_vector a, t_vector b)
{
    return (t_vector){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vector vector_subtract(t_vector a, t_vector b)
{
    return (t_vector){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_vector vector_scale(t_vector v, double scalar)
{
    return (t_vector){v.x * scalar, v.y * scalar, v.z * scalar};
}

t_vector vector_negate(t_vector v)
{
    return (t_vector){-v.x, -v.y, -v.z};
}

double vector_dot(t_vector a, t_vector b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector vector_cross(t_vector a, t_vector b)
{
    return (t_vector){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

double vector_length(t_vector v)
{
    return sqrt(vector_dot(v, v));
}

t_vector vector_normalize(t_vector v)
{
    double length = vector_length(v);
    if (length == 0)
        return (t_vector){0, 0, 0}; // Handle zero-length vector
    return vector_scale(v, 1.0 / length);
}