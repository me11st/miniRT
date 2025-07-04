# miniRT - Advanced Ray Tracer with Real-Time Display

A comprehensive ray tracer implementation for 42 school project with both real-time MLX display and PPM export capabilities.

## ✨ Features

- 🎯 **Complete Ray Tracing Engine**
  - Sphere, Plane, and Cylinder objects with accurate intersection algorithms
  - Point lights, directional lights, and ambient lighting
  - Lambertian (diffuse) shading with proper light calculations
  - Configurable camera system (position, direction, FOV)

- 🖥️ **Real-Time MLX Display**
  - Interactive window with live rendering
  - WASD camera movement controls
  - Arrow key camera rotation
  - ESC to exit
  - Real-time scene updates

- 📁 **File I/O**
  - Scene file parser supporting miniRT format
  - PPM image export for high-quality output
  - Default scene generation when no file provided

- 🔧 **Development Features**
  - Automatic MLX library download and compilation
  - Clean modular architecture
  - Linux-compatible build system
  - Comprehensive error handling

## 🚀 Usage

### Real-Time Display Mode
```bash
make
./miniRT scene_file.rt --display
```

### PPM Export Mode
```bash
make
./miniRT scene_file.rt --export
```

### Default Mode (Both display and export)
```bash
make
./miniRT scene_file.rt
```

## 🎮 Controls (MLX Display Mode)

- **WASD**: Move camera (forward, left, back, right)
- **Arrow Keys**: Rotate camera view
- **ESC**: Exit program
- Camera position and direction are displayed in console during movement

## 📝 Scene File Format

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

## 🔨 Building

The project automatically handles all dependencies:
- **MLX Library**: Automatically cloned from https://github.com/42Paris/minilibx-linux.git
- **GCC Compiler**: Standard C compiler
- **Math Library**: Linked automatically (-lm)
- **X11 Libraries**: For Linux graphics (Xext, X11)

### Build Commands
```bash
# Build the project (automatically downloads and compiles MLX)
make

# Clean build artifacts
make clean

# Complete clean (removes MLX as well)
make fclean

# Rebuild everything
make re
```

### First Build
On first build, the Makefile will:
1. Clone the MLX library repository
2. Compile MLX with appropriate flags
3. Build miniRT with MLX integration

## 📁 Project Structure

```
├── Makefile              # Build system with automatic MLX setup
├── README.md             # This file
├── test_scene.rt         # Example scene file
├── .gitignore           # Git ignore rules (excludes MLX, builds, outputs)
├── includes/
│   ├── minirt.h         # Main header with function prototypes
│   ├── vector.h         # 3D vector mathematics
│   ├── ray.h            # Ray structures and operations
│   ├── objects.h        # Object definitions and intersections
│   ├── scene.h          # Scene management and camera
│   ├── light.h          # Lighting system (ambient, point, directional)
│   └── color.h          # Color operations and conversions
└── srcs/
    ├── main.c           # Entry point and mode selection
    ├── parser.c         # Scene file parsing and validation
    ├── render.c         # Core ray tracing engine
    ├── scene.c          # Scene management and PPM export
    ├── mlx_display.c    # MLX integration and real-time display
    ├── vector.c         # Vector mathematics implementation
    ├── ray.c            # Ray operations and generic intersections
    ├── light.c          # Lighting calculations
    ├── color.c          # Color space operations
    └── objects/
        ├── sphere.c     # Sphere intersection algorithms
        ├── plane.c      # Plane intersection algorithms
        └── cylinder.c   # Cylinder intersection algorithms
```

## 🖼️ Output Formats

### PPM Images
The program generates PPM (Portable Pixmap) files that can be:
- Viewed with most image viewers
- Converted to other formats using ImageMagick:
```bash
# Convert PPM to PNG
convert output.ppm output.png

# Convert PPM to JPEG
convert output.ppm output.jpg
```

### Real-Time Display
- Live MLX window with interactive controls
- Immediate visual feedback during camera movement
- Console output showing camera position and orientation

## 🚀 Advanced Features

### Camera System
- **Position**: 3D world coordinates
- **Direction**: Normalized view direction vector
- **FOV**: Field of view in degrees
- **Aspect Ratio**: Automatically calculated from image dimensions

### Lighting Model
- **Ambient**: Global illumination with color and intensity
- **Point**: Positioned light sources with distance falloff
- **Directional**: Parallel light rays (like sunlight)
- **Diffuse Shading**: Lambertian reflection model

### Object Intersection
- **Sphere**: Quadratic equation solving with proper t-value selection
- **Plane**: Point-normal form with ray-plane intersection
- **Cylinder**: Finite cylinder with caps and height constraints

## 🎯 Performance Notes

- **Rendering Speed**: ~800x600 scene renders in 1-3 seconds on modern hardware
- **Memory Usage**: Efficient dynamic arrays for objects and lights
- **Real-Time**: Interactive camera movement with immediate re-rendering

## 🔮 Future Enhancements

Potential additions for extended versions:
- **Reflection/Refraction**: Mirror and glass materials
- **Shadows**: Ray tracing to light sources
- **Specular Highlights**: Phong/Blinn-Phong shading
- **Texture Mapping**: UV coordinates and image textures
- **Anti-Aliasing**: Multi-sampling for smoother edges
- **Acceleration Structures**: BVH or octree for complex scenes
- **Multi-Threading**: Parallel ray tracing for faster rendering
- **More Primitives**: Triangles, torus, etc.

## 📋 42 School Compliance

This project follows 42 school standards:
- ✅ Norm-compliant code formatting
- ✅ No external libraries except MLX (auto-downloaded)
- ✅ Proper error handling and memory management
- ✅ Makefile with standard rules (all, clean, fclean, re)
- ✅ Only .c and .h files in repository (MLX auto-managed)
- ✅ Comprehensive documentation

---

**Author**: [Your GitHub Username]  
**Project**: miniRT (42 School)  
**Repository**: https://github.com/me11st/miniRT
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
