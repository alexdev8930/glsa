# GLSA (Graphics Library Shader API)

GLSA is a C++ rendering library built on OpenGL. It provides functions for drawing graphics without requiring you to write shader code for each task. OpenGL is still required to run a GLSA program; GLSA handles the shaders behind the rendering functions it provides.

## What it gives you

- Header-only C++ API
- Render through C++ functions without writing shader code yourself
- Built-in helpers for common shapes like circles and rectangles (3D later)
- Less boilerplate for common rendering tasks
- Clean `glsa::` namespace
- A fast path for custom graphics work without writing everything from scratch

## Project layout

This repo is intentionally small. Most of the work lives in one header (maybe more later):

- `include/glsa/glsa.h` - Main library header.
- `examples/` - Example programs demonstrating GLSA.
- `docs/` - Documentation about GLSA

See [CONTRIBUTING.md](CONTRIBUTING.md) for contribution rules.   
See [CHANGELOG.md](CHANGELOG.md) for official release history
See [api_spec.md](docs/api_spec.md) for the API specification.    

> [!NOTE]
> The main header file is still being built so the GLSA API is not usable yet.

## Dependencies

To build and run the example on Linux, install:

- **Compiler:** Clang with C++17 support.
- **Build system:** CMake.
- **Build tools:** GNU Make and Ninja are needed for the `make run` shortcut. They are optional if you configure and build with CMake directly using another generator.
- **GLAD generator:** Python 3. CMake downloads and builds GLAD automatically, but GLAD's build uses Python to generate its loader.
- **FetchContent:** Git, used by CMake to download GLAD.
- **Libraries:** GLFW, GLM, and OpenGL development files.
- **Runtime:** An OpenGL 3.3-capable graphics driver.

## Linux Installation Commands

**Debian / Ubuntu / Mint / Pop!_OS:**
```bash
sudo apt update && sudo apt install clang cmake make ninja-build python3 git libglfw3-dev libglm-dev libgl1-mesa-dev
```

**Arch Linux / Manjaro**
```bash
sudo pacman -Syu && sudo pacman -S clang cmake make ninja python git glfw glm mesa
```

**Fedora:**
```bash
sudo dnf check-update && sudo dnf install clang cmake make ninja-build python3 git glfw-devel glm-devel mesa-libGL-devel
```

## Running the examples

To build and run the provided demo project, navigate to the `examples` folder and use CMake. This will automatically download and generate GLAD for you.

```bash
make run
```
