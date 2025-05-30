#include "minirt.h"

int main(int argc, char **argv)
{
    // Initialize the miniRT program
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <scene_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Load the scene from the provided file
    t_scene scene;
    if (parse_scene(argv[1], &scene) != 0)
    {
        fprintf(stderr, "Error parsing scene file: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    // Set up the rendering process
    render_scene(&scene);

    // Clean up resources
    free_scene(&scene);

    return EXIT_SUCCESS;
}