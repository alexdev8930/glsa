# Contributing to GLSA

Thanks for wanting to help out with GLSA! Since this is a single-header library, the goal is to keep things simple, fast, and organized.

## Rules for code changes

If you want to add code or make a change, please keep these guidelines in mind:
- **Keep it single-header:** All the main library logic has to stay inside `include/glsa/glsa.h` using the `GLSA_IMPLEMENTATION` guard. Don't add extra `.cpp` files to the library.
- **Don't add bloat:** We use OpenGL, GLAD, and GLM. Don't introduce heavy third-party libraries outside of those.
- **Use the GPU:** Features should rely on native GLSL shaders handled behind the scenes, not slow CPU pixel loops.

## How to help

### 1. Issues and bugs
If you find a bug or have a feature idea, just open an issue on the repo. Explain what is happening and provide a small code snippet if you can so it is easy to replicate.

### 2. Pull requests
- Fork the repo and make a new branch.
- Keep your changes focused on fixing one specific thing.
- Make sure it compiles smoothly with C++17 on Linux using `g++`.
- If you add a new public function to the `glsa::` namespace document it in [docs/api_spec.md](docs/api_spec.md).

## Code of Conduct

Be cool, respectful, and helpful in issues and PRs. If you need to report anything weird or toxic, you can reach out directly at **alexdev8930@proton.me**.
