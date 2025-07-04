#include "minirt.h"
#include "light.h"
#include "vector.h"
#include "color.h"

t_light create_ambient_light(t_color color, double intensity)
{
    t_light light;
    
    light.type = AMBIENT_LIGHT;
    light.color = color;
    light.intensity = intensity;
    light.brightness = 1.0;
    return light;
}

t_light create_point_light(t_vector position, t_color color, double intensity)
{
    t_light light;
    
    light.type = POINT_LIGHT;
    light.position = position;
    light.color = color;
    light.intensity = intensity;
    light.brightness = 1.0;
    return light;
}

t_light create_directional_light(t_vector direction, t_color color, double intensity)
{
    t_light light;
    
    light.type = DIRECTIONAL_LIGHT;
    light.direction = vector_normalize(direction);
    light.color = color;
    light.intensity = intensity;
    light.brightness = 1.0;
    return light;
}

t_color calculate_lighting(t_light light, t_vector point, t_vector normal, t_vector view_dir, t_color object_color)
{
    t_color result = create_color(0, 0, 0);
    (void)view_dir; // Unused for now, but may be used for specular lighting later
    
    if (light.type == AMBIENT_LIGHT)
    {
        result = color_multiply(light.color, light.intensity);
        result = color_blend(result, object_color);
    }
    else if (light.type == POINT_LIGHT)
    {
        t_vector light_dir = vector_subtract(light.position, point);
        light_dir = vector_normalize(light_dir);
        
        double dot_product = vector_dot(normal, light_dir);
        if (dot_product > 0)
        {
            t_color diffuse = color_multiply(light.color, light.intensity * dot_product);
            diffuse = color_blend(diffuse, object_color);
            result = color_add(result, diffuse);
        }
    }
    else if (light.type == DIRECTIONAL_LIGHT)
    {
        t_vector light_dir = vector_negate(light.direction);
        
        double dot_product = vector_dot(normal, light_dir);
        if (dot_product > 0)
        {
            t_color diffuse = color_multiply(light.color, light.intensity * dot_product);
            diffuse = color_blend(diffuse, object_color);
            result = color_add(result, diffuse);
        }
    }
    
    return color_clamp(result);
}