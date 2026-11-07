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

See [CONTRIBUTING.md](CONTRIBUTING.md) for contribution rules.   
See [CHANGELOG.md](CHANGELOG.md) for official release history
See [api_spec.md](docs/api_spec.md) for the API specification.    

> [!NOTE]
> The main header file is still being built so the GLSA API is not usable yet.

## Dependencies

To build and run this project, you need the following dependencies available on your system:

- **Compiler:** Clang (supporting C++17 or newer)
- **Math Library:** GLM (OpenGL Mathematics)
- **Windowing/Input:** GLFW
- **Graphics API:** OpenGL 3.3 Core Profile drivers
- **OpenGL Loader:** GLAD

## Installation Commands (Linux)

**Debian / Ubuntu / Mint / Pop!_OS:**
```bash
sudo apt update && sudo apt install clang libglfw3-dev libglm-dev
```

**Arch Linux / Manjaro**
```bash
sudo pacman -Syu && sudo pacman -S clang glfw glm
```

**Fedora:**
```bash
sudo dnf check-update && sudo dnf install clang glfw-devel glm-devel
```

## Running the examples

To build and run the provided demo project, navigate to the `examples` folder and use CMake. This will automatically download and generate GLAD for you.

### Generate the build folder

```bash
cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
```

### Build Examples and Run

```bash
cmake --build build
./build/glsa_demo
```
