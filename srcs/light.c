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
    return (light);
}

t_light create_point_light(t_vector position, t_color color, double intensity)
{
    t_light light;
    
    light.type = POINT_LIGHT;
    light.position = position;
    light.color = color;
    light.intensity = intensity;
    light.brightness = 1.0;
    return (light);
}

t_light create_directional_light(t_vector direction, t_color color, double intensity)
{
    t_light light;
    
    light.type = DIRECTIONAL_LIGHT;
    light.direction = vector_normalize(direction);
    light.color = color;
    light.intensity = intensity;
    light.brightness = 1.0;
    return (light);
}

// Helper function to calculate ambient lighting
static t_color calculate_ambient_lighting(t_light *light, t_lighting_context ctx)
{
    t_color result;
    
    result = color_multiply(light->color, light->intensity);
    result = color_blend(result, ctx.object_color);
    return (result);
}

// Helper function to calculate point light lighting
static t_color calculate_point_lighting(t_light *light, t_lighting_context ctx)
{
    t_color result;
    
    result = create_color(0, 0, 0);
    light->light_dir = vector_subtract(light->position, ctx.point);
    light->light_dir = vector_normalize(light->light_dir);
    light->dot_product = vector_dot(ctx.normal, light->light_dir);
    if (light->dot_product > 0)
    {
        light->diffuse = color_multiply(light->color, light->intensity * light->dot_product);
        light->diffuse = color_blend(light->diffuse, ctx.object_color);
        result = color_add(result, light->diffuse);
    }
    return (result);
}

// Helper function to calculate directional light lighting
static t_color calculate_directional_lighting(t_light *light, t_lighting_context ctx)
{
    t_color result;
    
    result = create_color(0, 0, 0);
    light->light_dir = vector_negate(light->direction);
    light->dot_product = vector_dot(ctx.normal, light->light_dir);
    if (light->dot_product > 0)
    {
        light->diffuse = color_multiply(light->color, light->intensity * light->dot_product);
        light->diffuse = color_blend(light->diffuse, ctx.object_color);
        result = color_add(result, light->diffuse);
    }
    return (result);
}

t_color calculate_lighting(t_light *light, t_lighting_context ctx)
{
    t_color result;

    result = create_color(0, 0, 0);
    if (light->type == AMBIENT_LIGHT)
        result = calculate_ambient_lighting(light, ctx);
    else if (light->type == POINT_LIGHT)
        result = calculate_point_lighting(light, ctx);
    else if (light->type == DIRECTIONAL_LIGHT)
        result = calculate_directional_lighting(light, ctx);
    return (color_clamp(result));
}