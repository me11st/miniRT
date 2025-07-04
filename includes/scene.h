#ifndef SCENE_H
#define SCENE_H

#include "objects.h"
#include "light.h"
#include "vector.h"
#include "color.h"

typedef struct s_camera {
    t_vector position;
    t_vector direction;
    t_vector up;
    double fov;         // Field of view in degrees
    double aspect_ratio;
} t_camera;

typedef struct s_image {
    int width;
    int height;
    int *data;          // RGB data
    void *mlx_ptr;      // MLX pointer
    void *win_ptr;      // Window pointer
    void *img_ptr;      // Image pointer
    char *addr;         // Image address
    int bits_per_pixel;
    int line_length;
    int endian;
} t_image;

typedef struct s_scene {
    t_camera camera;
    t_image image;
    t_object *objects;  // Dynamic array of objects
    t_light *lights;    // Dynamic array of lights
    int object_count;
    int light_count;
    int max_objects;    // Capacity of objects array
    int max_lights;     // Capacity of lights array
} t_scene;

// Function prototypes
t_scene *create_scene(int width, int height);
void init_camera(t_camera *camera, t_vector pos, t_vector target, double fov);
void add_object(t_scene *scene, t_object object);
void add_light(t_scene *scene, t_light light);
void free_scene(t_scene *scene);

// Image functions
t_image *create_image(int width, int height);
void put_pixel(t_image *image, int x, int y, t_color color);
void export_image_ppm(t_image *image, const char *filename);
void free_image(t_image *image);

// MLX functions
void init_mlx_display(t_scene *scene);
void display_scene(t_scene *scene);
void put_pixel_mlx(t_image *image, int x, int y, t_color color);
int handle_key_press(int keycode, t_scene *scene);
int handle_close_window(t_scene *scene);
void cleanup_mlx(t_scene *scene);

#endif // SCENE_H