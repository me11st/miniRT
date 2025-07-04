#include "minirt.h"
#include "objects.h"
#include "scene.h"
#include "vector.h"
#include "color.h"
#include "light.h"
#include <string.h>

void parse_scene(const char *filename, t_scene *scene)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Warning: Could not open file %s, creating default scene\n", filename);
        create_default_scene(scene);
        return;
    }
    
    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        // Skip empty lines and comments
        if (line[0] == '\n' || line[0] == '#')
            continue;
            
        char *tokens[10];
        int token_count = tokenize_line(line, tokens);
        
        if (token_count > 0)
        {
            if (strcmp(tokens[0], "A") == 0)
                parse_ambient_light(tokens, token_count, scene);
            else if (strcmp(tokens[0], "C") == 0)
                parse_camera(tokens, token_count, scene);
            else if (strcmp(tokens[0], "L") == 0)
                parse_light(tokens, token_count, scene);
            else if (strcmp(tokens[0], "sp") == 0)
                parse_sphere(tokens, token_count, scene);
            else if (strcmp(tokens[0], "pl") == 0)
                parse_plane(tokens, token_count, scene);
            else if (strcmp(tokens[0], "cy") == 0)
                parse_cylinder(tokens, token_count, scene);
        }
    }
    
    fclose(file);
}

void create_default_scene(t_scene *scene)
{
    printf("Creating default scene...\n");
    
    // Set up camera
    init_camera(&scene->camera, 
                create_vector(0, 0, 5), 
                create_vector(0, 0, 0), 
                60.0);
    
    // Add ambient light
    t_light ambient = create_ambient_light(create_color(1, 1, 1), 0.2);
    add_light(scene, ambient);
    
    // Add point light
    t_light point = create_point_light(create_vector(-2, 4, 4), create_color(1, 1, 1), 0.8);
    add_light(scene, point);
    
    // Add sphere
    t_object sphere = create_sphere(create_vector(0, 0, 0), 1.0, create_color(1, 0, 0));
    add_object(scene, sphere);
    
    // Add plane (floor)
    t_object plane = create_plane(create_vector(0, -2, 0), create_vector(0, 1, 0), create_color(0.8, 0.8, 0.8));
    add_object(scene, plane);
}

int tokenize_line(char *line, char **tokens)
{
    int count = 0;
    char *token = strtok(line, " \t\n");
    
    while (token && count < 10)
    {
        tokens[count] = token;
        count++;
        token = strtok(NULL, " \t\n");
    }
    
    return count;
}

void parse_camera(char **tokens, int count, t_scene *scene)
{
    if (count >= 4)
    {
        t_vector pos = parse_vector(tokens[1]);
        t_vector dir = parse_vector(tokens[2]);
        double fov = atof(tokens[3]);
        
        scene->camera.position = pos;
        scene->camera.direction = vector_normalize(dir);
        scene->camera.fov = fov;
    }
}

void parse_ambient_light(char **tokens, int count, t_scene *scene)
{
    if (count >= 3)
    {
        double intensity = atof(tokens[1]);
        t_color color = parse_color(tokens[2]);
        
        t_light ambient = create_ambient_light(color, intensity);
        add_light(scene, ambient);
    }
}

void parse_light(char **tokens, int count, t_scene *scene)
{
    if (count >= 4)
    {
        t_vector pos = parse_vector(tokens[1]);
        double intensity = atof(tokens[2]);
        t_color color = parse_color(tokens[3]);
        
        t_light light = create_point_light(pos, color, intensity);
        add_light(scene, light);
    }
}

void parse_sphere(char **tokens, int count, t_scene *scene)
{
    if (count >= 4)
    {
        t_vector center = parse_vector(tokens[1]);
        double radius = atof(tokens[2]);
        t_color color = parse_color(tokens[3]);
        
        t_object sphere = create_sphere(center, radius, color);
        add_object(scene, sphere);
    }
}

void parse_plane(char **tokens, int count, t_scene *scene)
{
    if (count >= 4)
    {
        t_vector point = parse_vector(tokens[1]);
        t_vector normal = parse_vector(tokens[2]);
        t_color color = parse_color(tokens[3]);
        
        t_object plane = create_plane(point, normal, color);
        add_object(scene, plane);
    }
}

void parse_cylinder(char **tokens, int count, t_scene *scene)
{
    if (count >= 6)
    {
        t_vector center = parse_vector(tokens[1]);
        t_vector direction = parse_vector(tokens[2]);
        double radius = atof(tokens[3]);
        double height = atof(tokens[4]);
        t_color color = parse_color(tokens[5]);
        
        t_object cylinder = create_cylinder(center, radius, height, direction, color);
        add_object(scene, cylinder);
    }
}

t_vector parse_vector(char *str)
{
    double x, y, z;
    sscanf(str, "%lf,%lf,%lf", &x, &y, &z);
    return create_vector(x, y, z);
}

t_color parse_color(char *str)
{
    int r, g, b;
    sscanf(str, "%d,%d,%d", &r, &g, &b);
    return create_color(r / 255.0, g / 255.0, b / 255.0);
}