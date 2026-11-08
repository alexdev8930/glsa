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

## Dependency Management

GLFW and GLM are declared in `vcpkg.json` and installed automatically by CMake in manifest mode. The vcpkg registry baseline pins their versions. GLAD is fetched at a pinned version by CMake and generated during the build, which requires Python 3. GLAD is generated through OpenGL 4.6; the intended support range is OpenGL 3.3-4.6 on Windows/Linux and 3.3-4.1 on macOS. A generated loader does not guarantee that a context supports every function: GLSA must check the active context version before using newer features. No OpenGL development package is directly linked by this example; an OpenGL-capable graphics driver is required at runtime.

You need CMake 3.21 or newer, Git, Python 3, vcpkg, and a C++17 compiler. The Linux preset uses Clang and Ninja; the Windows preset uses Visual Studio 2022 and MSVC.

## Setup

### Linux

Install the build tools for your distribution:

**Debian / Ubuntu:**

```bash
sudo apt update && sudo apt install build-essential clang cmake ninja-build python3 git curl zip unzip tar pkg-config autoconf autoconf-archive automake libtool
```

**Arch Linux:**

```bash
sudo pacman -Syu
sudo pacman -S --needed base-devel clang cmake ninja python git curl zip unzip tar pkgconf autoconf autoconf-archive automake libtool
```

**Fedora:**

```bash
sudo dnf group install "Development Tools"
sudo dnf install clang cmake ninja-build python3 git curl zip unzip tar pkgconf-pkg-config autoconf autoconf-archive automake libtool
```

Install vcpkg once by cloning and bootstrapping its official repository. CMake then reads `vcpkg.json` and installs the pinned GLFW and GLM versions automatically:

```bash
git clone https://github.com/microsoft/vcpkg "$HOME/vcpkg"
"$HOME/vcpkg/bootstrap-vcpkg.sh"
export VCPKG_ROOT="$HOME/vcpkg"
cmake --preset linux
cmake --build --preset linux
```

The first configure downloads and builds the declared dependencies. Build explicitly with `make linux`, or use `make run` to build and launch the demo. You can also use the CMake preset commands directly.

#### OpenGL Runtime Driver

GLAD is only the function loader; it does not provide an OpenGL implementation. You need a driver that supports the OpenGL version your program requests. If your system does not already have a suitable GPU-vendor driver, Mesa's runtime drivers can be installed with:

- Debian / Ubuntu: `sudo apt install libgl1-mesa-dri`
- Arch Linux: `sudo pacman -S mesa`
- Fedora: `sudo dnf install mesa-dri-drivers`

These are runtime drivers, not GLAD build dependencies. Do not install them if you already use a suitable proprietary GPU driver.

### Windows

Install Visual Studio 2022 with the **Desktop development with C++** workload, plus CMake, Git, and Python 3. Then bootstrap vcpkg from PowerShell:

```powershell
git clone https://github.com/microsoft/vcpkg C:\vcpkg
& C:\vcpkg\bootstrap-vcpkg.bat
$env:VCPKG_ROOT = "C:\vcpkg"
cmake --preset windows-msvc
cmake --build --preset windows-msvc
```

The first CMake configure installs GLFW and GLM from the manifest automatically.
With GNU Make installed, build the MSVC preset with `make windows` instead of running the two CMake commands separately.
