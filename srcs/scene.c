#include "minirt.h"
#include "scene.h"
#include <stdlib.h>

t_scene *create_scene(int width, int height)
{
    t_scene *scene = malloc(sizeof(t_scene));
    if (!scene)
        return NULL;
    
    // Initialize image
    scene->image.width = width;
    scene->image.height = height;
    scene->image.data = malloc(width * height * sizeof(int));
    if (!scene->image.data)
    {
        free(scene);
        return NULL;
    }
    
    // Initialize arrays with initial capacity
    scene->max_objects = 10;
    scene->max_lights = 5;
    scene->objects = malloc(scene->max_objects * sizeof(t_object));
    scene->lights = malloc(scene->max_lights * sizeof(t_light));
    
    if (!scene->objects || !scene->lights)
    {
        free(scene->image.data);
        free(scene->objects);
        free(scene->lights);
        free(scene);
        return NULL;
    }
    
    scene->object_count = 0;
    scene->light_count = 0;
    
    // Initialize camera with default values
    scene->camera.position = create_vector(0, 0, 0);
    scene->camera.direction = create_vector(0, 0, -1);
    scene->camera.up = create_vector(0, 1, 0);
    scene->camera.fov = 60.0;
    scene->camera.aspect_ratio = (double)width / height;
    
    return scene;
}

void init_camera(t_camera *camera, t_vector pos, t_vector target, double fov)
{
    camera->position = pos;
    camera->direction = vector_normalize(vector_subtract(target, pos));
    camera->up = create_vector(0, 1, 0);
    camera->fov = fov;
}

void add_object(t_scene *scene, t_object object)
{
    if (scene->object_count >= scene->max_objects)
    {
        // Resize array
        scene->max_objects *= 2;
        scene->objects = realloc(scene->objects, scene->max_objects * sizeof(t_object));
    }
    
    scene->objects[scene->object_count] = object;
    scene->object_count++;
}

void add_light(t_scene *scene, t_light light)
{
    if (scene->light_count >= scene->max_lights)
    {
        // Resize array
        scene->max_lights *= 2;
        scene->lights = realloc(scene->lights, scene->max_lights * sizeof(t_light));
    }
    
    scene->lights[scene->light_count] = light;
    scene->light_count++;
}

void put_pixel(t_image *image, int x, int y, t_color color)
{
    if (x >= 0 && x < image->width && y >= 0 && y < image->height)
    {
        int index = y * image->width + x;
        image->data[index] = color_to_int(color);
    }
}

void free_scene(t_scene *scene)
{
    if (scene)
    {
        free(scene->image.data);
        free(scene->objects);
        free(scene->lights);
        free(scene);
    }
}

// Image export functions
void export_image_ppm(t_image *image, const char *filename);

// Export functions
void export_image_ppm(t_image *image, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Error: Could not create file %s\n", filename);
        return;
    }
    
    // Write PPM header
    fprintf(file, "P3\n%d %d\n255\n", image->width, image->height);
    
    // Write pixel data
    for (int y = 0; y < image->height; y++)
    {
        for (int x = 0; x < image->width; x++)
        {
            int color_int = image->data[y * image->width + x];
            int r = (color_int >> 16) & 0xFF;
            int g = (color_int >> 8) & 0xFF;
            int b = color_int & 0xFF;
            fprintf(file, "%d %d %d ", r, g, b);
        }
        fprintf(file, "\n");
    }
    
    fclose(file);
    printf("Image exported to %s\n", filename);
}
