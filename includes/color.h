#ifndef COLOR_H
#define COLOR_H

typedef struct s_color {
    double r; // Red component (0.0 to 1.0)
    double g; // Green component (0.0 to 1.0)
    double b; // Blue component (0.0 to 1.0)
} t_color;

// Color operations
t_color create_color(double r, double g, double b);
t_color color_add(t_color c1, t_color c2);
t_color color_multiply(t_color c, double scalar);
t_color color_blend(t_color c1, t_color c2);
t_color color_clamp(t_color c);
int color_to_int(t_color c);

// Predefined colors
#define COLOR_BLACK create_color(0.0, 0.0, 0.0)
#define COLOR_WHITE create_color(1.0, 1.0, 1.0)
#define COLOR_RED create_color(1.0, 0.0, 0.0)
#define COLOR_GREEN create_color(0.0, 1.0, 0.0)
#define COLOR_BLUE create_color(0.0, 0.0, 1.0)

#endif // COLOR_H