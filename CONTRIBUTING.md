# Contributing to GLSA

Thanks for wanting to help out with GLSA! 

## Rules for code changes

If you want to add code or make a change, please keep these guidelines in mind:
- **Keep it header-only:** The library can be split across multiple headers, but it must not require a separately compiled `.cpp` file. Put implementation definitions behind the `GLSA_IMPLEMENTATION` guard and define it in exactly one source file.
- **Keep dependencies minimal:** Don’t add a third-party dependency to the library without checking with me first. The core uses OpenGL, GLAD, and GLM; GLFW is used by the examples.    
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
