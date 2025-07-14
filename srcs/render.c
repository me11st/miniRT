#include "minirt.h"
#include "objects.h"
#include "vector.h"
#include "ray.h"
#include "scene.h"
#include "color.h"
#include "light.h"
#include <math.h>

void render_scene(t_scene *scene)
{
    int x, y;
    t_ray ray;
    t_color color;

    printf("Rendering scene %dx%d...\n", scene->image.width, scene->image.height);

    for (y = 0; y < scene->image.height; y++)
    {
        for (x = 0; x < scene->image.width; x++)
        {
            ray = create_camera_ray(scene, x, y);
            color = trace_ray(ray, scene, 0);
            if (scene->image.mlx_ptr)
                put_pixel_mlx(&scene->image, x, y, color);
            else
                put_pixel(&scene->image, x, y, color);
        }
        
        // Print progress
        if (y % 50 == 0)
            printf("Rendered line %d/%d\n", y, scene->image.height);
    }
    
    printf("Rendering complete!\n");
}

t_ray create_camera_ray(t_scene *scene, int x, int y)
{
    t_ray ray;
    t_camera *cam = &scene->camera;
    
    // Convert pixel coordinates to normalized device coordinates (-1 to 1)
    double px = (2.0 * x / scene->image.width) - 1.0;
    double py = 1.0 - (2.0 * y / scene->image.height);
    
    // Apply aspect ratio and field of view
    px *= cam->aspect_ratio * tan(cam->fov * M_PI / 360.0);
    py *= tan(cam->fov * M_PI / 360.0);
    
    // Create right and up vectors for camera space
    t_vector right = vector_normalize(vector_cross(cam->direction, cam->up));
    t_vector up = vector_cross(right, cam->direction);
    
    // Calculate ray direction
    t_vector direction = vector_add(cam->direction, 
                         vector_add(vector_scale(right, px), 
                                   vector_scale(up, py)));
    
    ray.origin = cam->position;
    ray.direction = vector_normalize(direction);
    return ray;
}

t_color trace_ray(t_ray ray, t_scene *scene, int depth)
{
    if (depth >= MAX_DEPTH)
        return create_color(0, 0, 0);
    
    double closest_t = INFINITY;
    int hit_object = -1;
    double t;
    
    // Find closest intersection
    for (int i = 0; i < scene->object_count; i++)
    {
        if (intersect_ray_with_object(ray, &scene->objects[i], &t))
        {
            if (t < closest_t)
            {
                closest_t = t;
                hit_object = i;
            }
        }
    }
    
    // No intersection - return background color
    if (hit_object == -1)
        return create_color(0.2, 0.3, 0.8); // Sky blue
    
    // Calculate intersection point and normal
    t_vector hit_point = vector_add(ray.origin, vector_scale(ray.direction, closest_t));
    t_vector normal = get_normal(&scene->objects[hit_object], hit_point);
    
    // Get object color
    t_color object_color;
    switch (scene->objects[hit_object].type)
    {
        case SPHERE:
            object_color = scene->objects[hit_object].shape.sphere.color;
            break;
        case PLANE:
            object_color = scene->objects[hit_object].shape.plane.color;
            break;
        case CYLINDER:
            object_color = scene->objects[hit_object].shape.cylinder.color;
            break;
        default:
            object_color = create_color(1, 0, 1); // Magenta for unknown
    }
    
    // Calculate lighting
    t_color final_color = create_color(0, 0, 0);
    
    for (int i = 0; i < scene->light_count; i++)
    {
        t_vector view_dir = vector_negate(ray.direction);
        t_lighting_context ctx = {hit_point, normal, view_dir, object_color};
        t_color light_contrib = calculate_lighting(&scene->lights[i], ctx);
        final_color = color_add(final_color, light_contrib);
    }
    
    // If no lights, just return object color with some ambient
    if (scene->light_count == 0)
        final_color = color_multiply(object_color, 0.3);
    
    return color_clamp(final_color);
}