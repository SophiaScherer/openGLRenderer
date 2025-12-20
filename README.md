# OpenGL Renderer

A foundational OpenGL rendering engine in C++ demonstrating core graphics programming concepts with custom GLSL shaders.

## Prerequisites

- CMake 3.10 or higher
- C++17 compatible compiler (GCC, Clang, MSVC)
- OpenGL 3.3 or higher

## Building

### Linux/macOS

```bash
mkdir build
cd build
cmake ..
make
```

### Windows

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## Running

After building, the executable will be in the `build` directory:

```bash
./openGLRenderer        # Linux/macOS
.\openGLRenderer.exe    # Windows
```

## Project Structure

```
openGLRenderer/
├── source/           # Source files
├── external/         # Third-party dependencies
├── tests/            # Unit tests
└── CMakeLists.txt    # Build configuration
```

## License

MIT License - see [LICENSE](LICENSE) for details.