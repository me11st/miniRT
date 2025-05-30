#include "minirt.h"
#include "objects.h"
#include "vector.h"
#include "ray.h"
#include "scene.h"

void render_scene(t_scene *scene)
{
    int x, y;
    t_ray ray;
    t_color color;

    for (y = 0; y < scene->height; y++)
    {
        for (x = 0; x < scene->width; x++)
        {
            ray = create_ray(scene, x, y);
            color = trace_ray(ray, scene);
            put_pixel(scene->image, x, y, color);
        }
    }
}

t_ray create_ray(t_scene *scene, int x, int y)
{
    t_ray ray;
    // Calculate ray direction based on camera position and pixel coordinates
    // Set ray origin and direction
    return ray;
}

t_color trace_ray(t_ray ray, t_scene *scene)
{
    t_color color;
    // Perform ray-object intersection tests and calculate color based on lighting
    return color;
}

void put_pixel(t_image *image, int x, int y, t_color color)
{
    // Set the pixel color in the image buffer
}