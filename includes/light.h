#ifndef LIGHT_H
#define LIGHT_H

#include "vector.h"
#include "color.h"

typedef enum e_light_type {
    AMBIENT_LIGHT,
    POINT_LIGHT,
    DIRECTIONAL_LIGHT
} t_light_type;

typedef struct s_light {
    t_light_type type;
    t_vector position;     // For point lights
    t_vector direction;    // For directional lights
    t_color color;
    double intensity;      // 0.0 to 1.0
    double brightness;     // Overall brightness factor
} t_light;

// Light functions
t_light create_ambient_light(t_color color, double intensity);
t_light create_point_light(t_vector position, t_color color, double intensity);
t_light create_directional_light(t_vector direction, t_color color, double intensity);
t_color calculate_lighting(t_light light, t_vector point, t_vector normal, t_vector view_dir, t_color object_color);

#endif // LIGHT_H