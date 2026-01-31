# OpenGL 2D Bouncing Ball

A simple 2D physics demo: a ball bounces off the window borders using OpenGL. Built with **GLFW** for windowing and **GLAD** for OpenGL loading.

## Features

- Ball drawn as a circle (line loop) with configurable radius and segment count
- Frame-rate independent motion using delta time
- Wall collision detection and velocity reflection (bounce)
- Position correction so the ball doesn’t sink into the walls
- Configurable window size, initial velocity, and ball radius

## Run

1. Build the project to produce `cutable.exe`.
2. Keep `glfw3.dll` in the same directory as `cutable.exe` (or on your PATH).
3. Run `cutable.exe`.

Press the window’s close button to exit (or add a key handler and call `glfwSetWindowShouldClose` to quit on e.g. Escape).

## Configuration

Edit globals in `src/main.cpp` to change behavior:

- `WINDOW_WIDTH`, `WINDOW_HEIGHT` — window size
- `RADIUS`, `SEGMENTS` — ball size and circle smoothness
- `VELOCITY`, `position` — initial velocity and position

