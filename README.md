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

- `include/glsa/glsa.h` - Main library header.
- `include/glsa/glsa_types.h` - GLSA Data Types
- `include/glsa/glsa_colors.h` - Predefined RGBA color constants (`glm::vec4`). 
- `include/glsa/detail/glsa_internal.h` - Internal runtime state and private helpers.
- `examples/` - Example programs demonstrating GLSA.
- `docs/` - Documentation about GLSA
- `tools` - Code generation scripts and maintainer utilities.
- `external` - Third-party dependencies (e.g., GLAD).

See [CONTRIBUTING.md](CONTRIBUTING.md) for contribution rules.  
See [CHANGELOG.md](CHANGELOG.md) for official release history.  
See [api_spec.md](docs/api_spec.md) for the API specification.  

## Whats next

- [ ] Upload vertex data to the GPU (`Buffer`, `setBufferData`)
- [ ] Link buffers to VAO attribute locations (`setVertexAttribPointer`)
- [ ] Built-in shader presets: `shaderPreset(type, name, version)` — e.g. `shaderPreset(vert, "basic", 330)`
- [ ] Indexed drawing (`drawElements`)
- [ ] Texture loading and binding
- [ ] Shader hot-reload at runtime
- [ ] Common shape helpers (`drawRectangle`, `drawCircle`)

## Dependency Management

GLFW and GLM are installed by CMake from `vcpkg.json` in manifest mode (pinned versions). The GLAD loader is pre-generated and checked into `external/glad/` — no Python needed to build. You need CMake 3.21+, Git, vcpkg, and a C++17 compiler. An OpenGL-capable graphics driver is required at runtime.

### Setup

Install your platform's compiler, CMake, Git, and window-system packages, then bootstrap vcpkg and build.

### Linux

The listed X11/Wayland packages build both GLFW backends; GLFW picks one at runtime.

**Debian / Ubuntu:**

```bash
sudo apt update && sudo apt install build-essential clang cmake ninja-build git curl zip unzip tar pkg-config autoconf autoconf-archive automake libtool xorg-dev libxinerama-dev libxcursor-dev libglu1-mesa-dev libwayland-dev libwayland-bin libxkbcommon-dev wayland-protocols extra-cmake-modules
```

**Arch Linux:**

```bash
sudo pacman -Syu
sudo pacman -S --needed base-devel clang cmake ninja git curl zip unzip tar pkgconf autoconf autoconf-archive automake libtool libxinerama libxcursor libxrandr libxi libx11 libxext libxrender libxfixes libxcb libxkbcommon wayland wayland-protocols glu extra-cmake-modules
```

**Fedora:**

```bash
sudo dnf group install "Development Tools"
sudo dnf install clang cmake ninja-build git curl zip unzip tar pkgconf-pkg-config autoconf autoconf-archive automake libtool xorg-x11-proto-devel libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel libXext-devel libXrender-devel libXfixes-devel libxkbcommon-devel wayland-devel wayland-protocols-devel mesa-libGLU-devel extra-cmake-modules
```

```bash
git clone https://github.com/microsoft/vcpkg "$HOME/vcpkg"
"$HOME/vcpkg/bootstrap-vcpkg.sh"
```

#### OpenGL Runtime Driver 

GLAD is only the function loader; it does not provide an OpenGL implementation. You need a driver that supports the OpenGL version your program requests. If your system does not already have a suitable GPU-vendor driver, Mesa's runtime drivers can be installed with:

- Debian / Ubuntu: `sudo apt install libgl1-mesa-dri`
- Arch Linux: `sudo pacman -S mesa`
- Fedora: `sudo dnf install mesa-dri-drivers`

These are runtime drivers, not GLAD build dependencies. Do not install them if you already use a suitable proprietary GPU driver.

### Windows

Install Visual Studio 2022 with the **Desktop development with C++** workload, plus CMake and Git. Then bootstrap vcpkg:

```powershell
git clone https://github.com/microsoft/vcpkg "$env:USERPROFILE\vcpkg"
& "$env:USERPROFILE\vcpkg\bootstrap-vcpkg.bat"
```

### MacOS

macOS needs no X11 or Wayland packages; Apple Clang comes with the Xcode Command Line Tools.

```bash
xcode-select --install
```
Install Homebrew if needed, then:

```bash
brew update
brew install cmake ninja git curl zip unzip pkgconf autoconf autoconf-archive automake libtool
```

```bash
git clone https://github.com/microsoft/vcpkg "$HOME/vcpkg"
"$HOME/vcpkg/bootstrap-vcpkg.sh"
```

### Build

CMake installs the pinned dependencies automatically, then builds and runs the examples:

```bash
cmake --preset linux
cmake --build --preset linux --target run-examples
```
Use `windows-msvc` on Windows or `macos` on MacOS in place of `linux`.
