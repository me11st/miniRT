# miniRT Project

miniRT is a simple ray tracing project that aims to render basic geometric shapes such as spheres, cylinders, and planes. This project serves as an educational tool to understand the fundamentals of ray tracing and 3D rendering.

## Project Structure

The project is organized into the following directories and files:

```
miniRT
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
   git clone https://github.com/me11st/miniRT.git
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
