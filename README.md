# opengl-module

A module-friendly way to start drawing graphics with OpenGL. Handles context creation, rendering loop, shaders, and more to come.

## Features

- Minimal boilerplate
- Organized shader pipeline
- Easy integration with existing projects
- OS-independent build via CMake
- Includes its own .c and .cpp files, which are automatically compiled when added as a subdirectory with cmake. (See [here](https://github.com/whatupo9/opengl-module?tab=readme-ov-file#Integrating-into-Your-Project))

## Getting Started

### Prerequisites

- OpenGL version 4.6 or newer
- A C++ compiler that supports at least C++11
- GLFW (for window and input handling)
- CMake version 3.10 or newer

You can install the dependencies using your system’s package manager or include them manually in your project.

### Integrating into Your Project

Example Project Structure:
```
/project
├── shaders/         # Store your OpenGL shaders here
├── opengl-module/ # The files from this repo
├── src/             # The source files for your project
└── CMakeLists.txt   # Your projects CMake build configuration (NOT THE ONE IN THIS REPO)
```

To include this OpenGL module in your own CMake-based project, add the following line to your `CMakeLists.txt`:
```
add_subdirectory(opengl-module)
```

## Shader Customization

By default, opengl-module looks for any shaders you use in a directory called `shaders` in the same directory as your `CMakeLists.txt`. See [above](https://github.com/whatupo9/opengl-module?tab=readme-ov-file#Integrating-into-Your-Project) for an example project folder structure.

If you want to customize where opengl-module looks for shaders, you can set the SHADERS_DIR variable in your `CMakeLists.txt`. This is used by the `Shader` class to look for any shader files given to it. For example, if you wanted to keep your shaders at `project/assets/shaders` instead, you would add the following line to your `CMakeLists.txt`:

```
set(SHADERS_DIR "${CMAKE_SOURCE_DIR}/assets/shaders")
```

## License

This project is licensed under the MIT License. See the `LICENSE` file for more information.

## Contributing

Contributions are welcome! If you have suggestions or fixes, feel free to open an issue or submit a pull request. For large changes, please start a discussion first.

## Author

**Cameron MacGillivary** — [@whatupo9](https://github.com/whatupo9)
