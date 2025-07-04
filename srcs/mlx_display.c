#include "minirt.h"
#include "scene.h"
#include "color.h"

// MLX key codes for Linux
#define KEY_ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

void init_mlx_display(t_scene *scene)
{
    // Initialize MLX
    scene->image.mlx_ptr = mlx_init();
    if (!scene->image.mlx_ptr)
    {
        printf("Error: Failed to initialize MLX\n");
        exit(1);
    }
    
    // Create window
    scene->image.win_ptr = mlx_new_window(scene->image.mlx_ptr, 
                                         scene->image.width, 
                                         scene->image.height, 
                                         "miniRT");
    if (!scene->image.win_ptr)
    {
        printf("Error: Failed to create window\n");
        exit(1);
    }
    
    // Create image for MLX
    scene->image.img_ptr = mlx_new_image(scene->image.mlx_ptr, 
                                        scene->image.width, 
                                        scene->image.height);
    if (!scene->image.img_ptr)
    {
        printf("Error: Failed to create image\n");
        exit(1);
    }
    
    // Get image data address
    scene->image.addr = mlx_get_data_addr(scene->image.img_ptr,
                                         &scene->image.bits_per_pixel,
                                         &scene->image.line_length,
                                         &scene->image.endian);
    
    printf("MLX initialized successfully\n");
    printf("Use ESC to exit, WASD to move camera, Arrow keys to rotate\n");
}

void put_pixel_mlx(t_image *image, int x, int y, t_color color)
{
    char *dst;
    int color_int;
    
    if (x >= 0 && x < image->width && y >= 0 && y < image->height)
    {
        color_int = color_to_int(color);
        dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
        *(unsigned int*)dst = color_int;
        
        // Also store in our data array for PPM export
        image->data[y * image->width + x] = color_int;
    }
}

void display_scene(t_scene *scene)
{
    // Put the rendered image to the window
    mlx_put_image_to_window(scene->image.mlx_ptr, 
                           scene->image.win_ptr, 
                           scene->image.img_ptr, 0, 0);
}

int handle_key_press(int keycode, t_scene *scene)
{
    double move_speed = 0.5;
    double rotate_speed = 0.1;
    int need_rerender = 0;
    
    // Movement
    if (keycode == KEY_W)
    {
        t_vector forward = vector_scale(scene->camera.direction, move_speed);
        scene->camera.position = vector_add(scene->camera.position, forward);
        need_rerender = 1;
    }
    else if (keycode == KEY_S)
    {
        t_vector backward = vector_scale(scene->camera.direction, -move_speed);
        scene->camera.position = vector_add(scene->camera.position, backward);
        need_rerender = 1;
    }
    else if (keycode == KEY_A)
    {
        t_vector right = vector_cross(scene->camera.direction, scene->camera.up);
        right = vector_normalize(right);
        t_vector left = vector_scale(right, -move_speed);
        scene->camera.position = vector_add(scene->camera.position, left);
        need_rerender = 1;
    }
    else if (keycode == KEY_D)
    {
        t_vector right = vector_cross(scene->camera.direction, scene->camera.up);
        right = vector_normalize(right);
        right = vector_scale(right, move_speed);
        scene->camera.position = vector_add(scene->camera.position, right);
        need_rerender = 1;
    }
    // Rotation (simplified - just change direction)
    else if (keycode == KEY_LEFT)
    {
        // Rotate camera left around Y axis
        double cos_r = cos(rotate_speed);
        double sin_r = sin(rotate_speed);
        t_vector new_dir;
        new_dir.x = scene->camera.direction.x * cos_r - scene->camera.direction.z * sin_r;
        new_dir.y = scene->camera.direction.y;
        new_dir.z = scene->camera.direction.x * sin_r + scene->camera.direction.z * cos_r;
        scene->camera.direction = vector_normalize(new_dir);
        need_rerender = 1;
    }
    else if (keycode == KEY_RIGHT)
    {
        // Rotate camera right around Y axis
        double cos_r = cos(-rotate_speed);
        double sin_r = sin(-rotate_speed);
        t_vector new_dir;
        new_dir.x = scene->camera.direction.x * cos_r - scene->camera.direction.z * sin_r;
        new_dir.y = scene->camera.direction.y;
        new_dir.z = scene->camera.direction.x * sin_r + scene->camera.direction.z * cos_r;
        scene->camera.direction = vector_normalize(new_dir);
        need_rerender = 1;
    }
    else if (keycode == KEY_ESC)
    {
        cleanup_mlx(scene);
        exit(0);
    }
    
    // Re-render if camera moved
    if (need_rerender)
    {
        printf("Rendering scene...\n");
        render_scene(scene);
        display_scene(scene);
        printf("Camera: pos(%.2f,%.2f,%.2f) dir(%.2f,%.2f,%.2f)\n",
               scene->camera.position.x, scene->camera.position.y, scene->camera.position.z,
               scene->camera.direction.x, scene->camera.direction.y, scene->camera.direction.z);
    }
    
    return 0;
}

int handle_close_window(t_scene *scene)
{
    cleanup_mlx(scene);
    exit(0);
    return 0;
}

void cleanup_mlx(t_scene *scene)
{
    if (scene->image.img_ptr)
        mlx_destroy_image(scene->image.mlx_ptr, scene->image.img_ptr);
    if (scene->image.win_ptr)
        mlx_destroy_window(scene->image.mlx_ptr, scene->image.win_ptr);
    if (scene->image.mlx_ptr)
    {
        mlx_destroy_display(scene->image.mlx_ptr);
        free(scene->image.mlx_ptr);
    }
    printf("MLX cleaned up\n");
}
