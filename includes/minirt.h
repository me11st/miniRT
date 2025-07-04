#ifndef MINIRT_H
#define MINIRT_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include "vector.h"
#include "ray.h"
#include "scene.h"
#include "objects.h"
#include "light.h"
#include "color.h"

// Define constants
#define WIDTH 800
#define HEIGHT 600
#define MAX_DEPTH 5

// Function prototypes
void init_miniRT(int argc, char **argv);
void render_scene(t_scene *scene);
void cleanup(void);

// Render functions
t_ray create_camera_ray(t_scene *scene, int x, int y);
t_color trace_ray(t_ray ray, t_scene *scene, int depth);

// Parser functions
void parse_scene(const char *filename, t_scene *scene);
void create_default_scene(t_scene *scene);
int tokenize_line(char *line, char **tokens);
void parse_camera(char **tokens, int count, t_scene *scene);
void parse_ambient_light(char **tokens, int count, t_scene *scene);
void parse_light(char **tokens, int count, t_scene *scene);
void parse_sphere(char **tokens, int count, t_scene *scene);
void parse_plane(char **tokens, int count, t_scene *scene);
void parse_cylinder(char **tokens, int count, t_scene *scene);
t_vector parse_vector(char *str);
t_color parse_color(char *str);

#endif // MINIRT_H