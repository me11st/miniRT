#ifndef SCENE_H
#define SCENE_H

#include "objects.h"
#include "light.h"

typedef struct s_scene {
    t_object *objects; // Pointer to an array of objects in the scene
    t_light *lights;    // Pointer to an array of lights in the scene
    int object_count;   // Number of objects in the scene
    int light_count;    // Number of lights in the scene
} t_scene;

// Function prototypes
t_scene *create_scene();
void add_object(t_scene *scene, t_object object);
void add_light(t_scene *scene, t_light light);
void free_scene(t_scene *scene);

#endif // SCENE_H