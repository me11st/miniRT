#include "minirt.h"
#include "color.h"

t_color create_color(double r, double g, double b) {
    t_color color;

    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}

t_color color_add(t_color c1, t_color c2) {
    return create_color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

t_color color_multiply(t_color c, double scalar) {
    return create_color(c.r * scalar, c.g * scalar, c.b * scalar);
}

t_color color_blend(t_color c1, t_color c2) {
    return create_color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
}

t_color color_clamp(t_color c) {
    t_color result;
    result.r = fmin(fmax(c.r, 0.0), 1.0);
    result.g = fmin(fmax(c.g, 0.0), 1.0);
    result.b = fmin(fmax(c.b, 0.0), 1.0);
    return result;
}

int color_to_int(t_color c) {
    t_color clamped = color_clamp(c);
    int r = (int)(clamped.r * 255);
    int g = (int)(clamped.g * 255);
    int b = (int)(clamped.b * 255);
    return (r << 16) | (g << 8) | b;
}