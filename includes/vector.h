#ifndef VECTOR_H
#define VECTOR_H

typedef struct s_vector {
    double x;
    double y;
    double z;
} t_vector;

t_vector vector_add(t_vector v1, t_vector v2);
t_vector vector_subtract(t_vector v1, t_vector v2);
t_vector vector_scale(t_vector v, double scalar);
double vector_dot(t_vector v1, t_vector v2);
t_vector vector_cross(t_vector v1, t_vector v2);
t_vector vector_normalize(t_vector v);

#endif // VECTOR_H