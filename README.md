# miniRT - Simple Ray Tracer

A basic ray tracer implementation for 42 school project.

## Features

- ✅ Sphere, Plane, and Cylinder objects
- ✅ Point lights, directional lights, and ambient lighting
- ✅ Basic Lambertian (diffuse) shading
- ✅ Scene file parsing
- ✅ PPM image export
- ✅ Configurable camera (position, direction, FOV)

## Usage

```bash
make
./miniRT scene_file.rt
```

The program will render the scene and export it to `output.ppm`.

## Scene File Format

The scene file uses a simple text format:

```
# Comments start with #

# Ambient lighting: intensity (0.0-1.0) color (R,G,B 0-255)
A 0.2 255,255,255

# Camera: position direction fov
C 0,0,5 0,0,-1 60

# Point Light: position intensity color
L -2,4,4 0.8 255,255,255

# Sphere: center radius color
sp 0,0,0 1.0 255,0,0

# Plane: point normal color
pl 0,-2,0 0,1,0 200,200,200

# Cylinder: center direction radius height color
cy 1,-1,0 0,1,0 0.3 2.0 255,255,0
```

## Building

The project requires:
- GCC compiler
- Math library (-lm)

Simply run `make` to build the project.

## File Structure

```
├── Makefile
├── README.md
├── includes/
│   ├── minirt.h      # Main header
│   ├── vector.h      # Vector operations
│   ├── ray.h         # Ray structures
│   ├── objects.h     # Object definitions
│   ├── scene.h       # Scene management
│   ├── light.h       # Lighting system
│   └── color.h       # Color operations
└── srcs/
    ├── main.c        # Entry point
    ├── parser.c      # Scene file parsing
    ├── render.c      # Ray tracing engine
    ├── scene.c       # Scene management
    ├── vector.c      # Vector math
    ├── ray.c         # Ray operations
    ├── light.c       # Lighting calculations
    ├── color.c       # Color operations
    └── objects/
        ├── sphere.c  # Sphere intersection
        ├── plane.c   # Plane intersection
        └── cylinder.c # Cylinder intersection
```

## Example Output

The program generates a PPM image file that can be viewed with image viewers that support the PPM format, or converted to other formats using tools like ImageMagick:

```bash
# Convert PPM to PNG
convert output.ppm output.png
```

## Next Steps

To extend this raytracer, you could add:
- Reflection and refraction
- Specular highlights
- Texture mapping
- Anti-aliasing
- More object types (triangles, torus, etc.)
- Shadow calculations
- MLX integration for real-time display
- Multi-threading for faster rendering
├── includes
│   ├── minirt.h        # Main definitions and includes for the miniRT project
│   ├── objects.h       # Structures and functions for geometric objects
│   ├── vector.h        # Vector structure and operations
│   ├── ray.h           # Ray structure and intersection functions
│   └── scene.h         # Scene management, including objects and lights
├── srcs
│   ├── main.c          # Entry point of the application
│   ├── parser.c        # Scene description parsing
│   ├── vector.c        # Vector operations implementation
│   ├── ray.c           # Ray operations implementation
│   ├── objects
│   │   ├── sphere.c    # Sphere object functions
│   │   ├── plane.c     # Plane object functions
│   │   └── cylinder.c   # Cylinder object functions
│   ├── light.c         # Light source functions
│   ├── color.c         # Color manipulation functions
│   └── render.c        # Rendering logic
├── Makefile             # Build instructions
└── README.md            # Project documentation
```

## Features

- **Geometric Objects**: Supports spheres, cylinders, and planes.
- **Ray Tracing**: Implements basic ray-object intersection tests.
- **Lighting**: Includes functionality for light sources and color calculations.
- **Scene Management**: Allows for the creation and management of scenes with multiple objects and lights.

## Setup Instructions

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/miniRT.git
   cd miniRT
   ```

2. Build the project using the Makefile:
   ```
   make
   ```

3. Run the application:
   ```
   ./miniRT
   ```

## Usage

To use the miniRT application, you will need to provide a scene description file that defines the objects and lights in the scene. The parser will read this file and set up the scene accordingly.

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue for any suggestions or improvements.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.