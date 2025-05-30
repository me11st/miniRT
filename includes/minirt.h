#ifndef MINIRT_H
#define MINIRT_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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
void render_scene(void);
void cleanup(void);

#endif // MINIRT_H