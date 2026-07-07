*This project has been created as part of the 42 curriculum by dakaymak, marudlof*

<a id="top"></a>

# miniRT

- [miniRT](#minirt)
	- [Description](#description)
	- [Features](#features)
	- [Rendering pipeline](#rendering-pipeline)
	- [Instructions](#instructions)
		- [Compilation](#compilation)
		- [Execution](#execution)
		- [Controls](#controls)
	- [Scene format (`.rt`)](#scene-format-rt)
	- [Project Structure](#project-structure)
	- [Technical Choices](#technical-choices)
	- [Resources](#resources)
	- [AI Usage](#ai-usage)
	- [Authors](#authors)

-----

## Description

**miniRT** is a simple ray tracer written in C, built as part of the 42
curriculum. It reads a scene described in a `.rt` text file, casts a primary ray
through every pixel of the window, computes ray/object intersections and displays
the result in a [MLX42](https://github.com/codam-coding-college/MLX42) window.

The project is built from scratch on top of two homemade libraries:

- **`libft`** — the 42 standard C library (strings, lists, memory, printf...).
- **`libvec`** — a 3D vector algebra library (`dot`, `cross`, `normalize`,
  `reflect`, `lerp`, `clamp`...) used for every geometric computation.

-----

## Features

Everything below is currently implemented:

- **Scene parsing** — reads the `.rt` file passed as the first argument, checks
  the `.rt` extension, and parses the identifiers `A`, `C`, `L`, `sp`, `pl`, `cy`
  in any order. `A`, `C` and `L` are enforced to appear exactly once.
- **Validation** — ratios in `[0,1]`, colors in `[0,255]`, FOV in `[0,180]`.
  Any error prints `Error\n` followed by an explicit message and exits cleanly,
  with no leak.
- **MLX42 window** — opens a `1280x720` window and draws into an image buffer.
- **Camera** — builds the camera basis (`right` / `up` / `forward`) from the
  orientation vector and generates one primary ray per pixel according to the FOV.
- **Ray/object intersections**
  - **Sphere** — quadratic equation.
  - **Plane** — dot product.
  - **Cylinder** — bounded lateral surface **plus the two caps**.
- **Closest hit** — iterates over the object list and keeps the nearest positive
  intersection, then computes the surface normal at the impact point.
- **Rendering** — each hit pixel is filled with the flat color of the closest
  object; background pixels show a gradient based on the ray direction.

-----

## Rendering pipeline

```
scene.rt
   ↓
 Parser        →  t_scene (ambient, camera, light, object list)
   ↓
 Camera setup  →  right / up / forward basis
   ↓
 for each pixel:
   Primary ray →  ft_primary_ray(camera, x, y)
   Closest hit →  ft_closest_hit  (sphere / plane / cylinder)
   Shading     →  object color  (background gradient if no hit)
   ↓
 MLX42 image → window
```

-----

## Instructions

### Compilation

```bash
git clone <repo_url> miniRT
cd miniRT
make
```

`make` builds `libft`, `libvec` and `MLX42` (via CMake) before linking the
`miniRT` executable. Available targets:

```bash
make        # Build everything
make clean  # Remove object files
make fclean # Remove objects, libraries and the executable
make re     # Full rebuild
```

> **Note:** MLX42 requires `cmake`, `glfw` and OpenGL to be installed on your
> system. Compilation uses `-Wall -Wextra -Werror`.

### Execution

```bash
./miniRT resources/scene.rt
```

Sample scenes are provided in `resources/`: `minimal.rt`, `sphere.rt`,
`plane.rt`, `cylinder.rt` and `scene.rt`.

### Controls

| Key            | Action              |
|----------------|---------------------|
| `ESC`          | Close the window    |
| Window close   | Close the window    |

-----

## Scene format (`.rt`)

Elements are separated by one or more spaces and can appear in any order.
`A`, `C` and `L` must be defined exactly once.

| Id   | Element  | Fields                                                          |
|------|----------|----------------------------------------------------------------|
| `A`  | Ambient  | ratio `[0,1]`, color `R,G,B`                                    |
| `C`  | Camera   | position `x,y,z`, orientation `[-1,1]`, FOV `[0,180]`           |
| `L`  | Light    | position `x,y,z`, brightness `[0,1]`, color `R,G,B`            |
| `sp` | Sphere   | center `x,y,z`, diameter, color `R,G,B`                        |
| `pl` | Plane    | point `x,y,z`, normal `[-1,1]`, color `R,G,B`                  |
| `cy` | Cylinder | center `x,y,z`, axis `[-1,1]`, diameter, height, color `R,G,B` |

Example (`resources/scene.rt`):

```
A 0.2 255,255,255
C 0,5,-60 0,0,1 70
L -40,50,-20 0.7 255,255,255
pl 0,-10,0 0,1,0 80,80,80
sp -25,0,20 20 255,0,0
sp 25,0,20 20 0,255,0
cy 0,-10,40 0,1,0 14.2 30 0,80,255
```

-----

## Project Structure

```
miniRT/
├── srcs/
│   ├── main.c          # Entry point, argument checking
│   ├── parser/         # .rt parsing, tokenizing, range validation
│   ├── render/         # Camera, primary rays, intersections, closest hit
│   ├── window/         # MLX42 window and event hooks (ESC / close)
│   ├── utils/          # Color packing, cleanup, error handling
│   └── gnl/            # get_next_line
├── includes/           # minirt.h, rt_types.h, rt_parser.h, rt_render.h
├── resources/          # Sample .rt scenes
├── libft/              # Custom C library
├── libvec/             # 3D vector algebra library
├── MLX42/              # Graphics library (submodule)
└── Makefile
```

-----

## Technical Choices

- **Objects** are stored in a `t_list` (linked list). Each `t_object` carries its
  type, its color and a `union` holding the sphere / plane / cylinder data, so a
  single list handles every primitive.
- **The cylinder center** is the midpoint of its axis: the body spans
  `±height/2` around it, and the two caps are tested separately from the lateral
  surface.
- **Colors** are handled as `t_vec3` (component-wise math) and packed into the
  RGBA integer expected by MLX42 only at the final write.
- **Error handling** always prints `Error\n` plus a message, frees the scene and
  exits without leaking.

-----

## Resources

- [MLX42 documentation](https://github.com/codam-coding-college/MLX42)
- [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
- [Scratchapixel — Ray Tracing](https://www.scratchapixel.com/)
- Ray/sphere, ray/plane and ray/cylinder intersection math

-----

## AI Usage

AI tools were used responsibly as a learning assistant:

- Explaining ray tracing concepts (intersection math, camera basis, normals)
- Code review and refactoring suggestions
- Debugging support
- Writing commit messages and documentation structure

All AI-generated content was reviewed, understood and adapted before use.

-----

## Authors

- **marudlof** — [codeberg.org/Vusk](https://codeberg.org/Vusk)
- **dakaymak**

*Built as part of the [42](https://42angouleme.fr/) curriculum.*
