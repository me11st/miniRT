#include "minirt.h"
#include "light.h"

t_light create_light(t_vector position, t_color color, double intensity)
{
    t_light light;

    light.position = position;
    light.color = color;
    light.intensity = intensity;
    return light;
}

t_color calculate_light_intensity(t_light light, t_vector point, t_vector normal)
{
    t_vector light_dir;
    double dot_product;
    t_color result;

    light_dir = vector_subtract(light.position, point);
    light_dir = vector_normalize(light_dir);
    dot_product = vector_dot(normal, light_dir);

    if (dot_product < 0)
        dot_product = 0;

    result = color_scale(light.color, light.intensity * dot_product);
    return result;
}