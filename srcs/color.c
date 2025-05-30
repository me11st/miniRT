#include "minirt.h"

typedef struct s_color {
    double r;
    double g;
    double b;
} t_color;

t_color create_color(double r, double g, double b) {
    t_color color;

    color.r = fmin(fmax(r, 0.0), 1.0);
    color.g = fmin(fmax(g, 0.0), 1.0);
    color.b = fmin(fmax(b, 0.0), 1.0);
    return color;
}

t_color add_colors(t_color c1, t_color c2) {
    return create_color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

t_color multiply_color(t_color color, double factor) {
    return create_color(color.r * factor, color.g * factor, color.b * factor);
}

t_color blend_colors(t_color c1, t_color c2, double ratio) {
    return create_color(
        c1.r * (1 - ratio) + c2.r * ratio,
        c1.g * (1 - ratio) + c2.g * ratio,
        c1.b * (1 - ratio) + c2.b * ratio
    );
}