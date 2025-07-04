#include "minirt.h"
#include "scene.h"

int main(int argc, char **argv)
{
    int display_mode = 0; // 0 = PPM export, 1 = MLX display
    
    // Initialize the miniRT program
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <scene_file> [--display]\n", argv[0]);
        fprintf(stderr, "  --display: Show real-time MLX window (default: export PPM)\n");
        return EXIT_FAILURE;
    }
    
    // Check for display mode flag
    if (argc >= 3 && ft_strcmp(argv[2], "--display") == 0)
        display_mode = 1;

    // Create scene
    t_scene *scene = create_scene(WIDTH, HEIGHT);
    if (!scene)
    {
        fprintf(stderr, "Error creating scene\n");
        return EXIT_FAILURE;
    }

    // Load the scene from the provided file
    parse_scene(argv[1], scene);

    if (display_mode)
    {
        // MLX real-time display mode
        init_mlx_display(scene);
        
        // Initial render
        printf("Rendering initial scene...\n");
        render_scene(scene);
        display_scene(scene);
        
        // Set up event handlers
        mlx_key_hook(scene->image.win_ptr, handle_key_press, scene);
        mlx_hook(scene->image.win_ptr, 17, 1L<<17, handle_close_window, scene);
        
        // Start MLX loop
        mlx_loop(scene->image.mlx_ptr);
    }
    else
    {
        // PPM export mode (original behavior)
        render_scene(scene);
        export_image_ppm(&scene->image, "output.ppm");
    }

    // Clean up resources
    free_scene(scene);

    return EXIT_SUCCESS;
}