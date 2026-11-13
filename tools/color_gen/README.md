# GLSA Color Header Generator

Generates `include/glsa/glsa_colors.h` from `lots_of_colors.json` as `inline constexpr glm::vec4` constants under `namespace glsa::colors`.

> [!WARNING]
> This is a maintainer utility and **is not intended for regular use**. Normal users of GLSA do not need to run this script `include/glsa/glsa_colors.h` is already pre-generated and ready to `#include` in your C++ project.


## Usage

If you ever need to regenerate `glsa_colors.h` after modifying `lots_of_colors.json`, follow these steps:

1. Make sure **Python 3** is installed on your system.
2. Run the generator from the root of the repository:

```bash
python3 tools/color_gen/json_to_header.py
```

*(Replace `python3` with `python` if you're on Windows.)*