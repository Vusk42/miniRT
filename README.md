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

- **`libft`** - the 42 standard C library (strings, lists, memory, printf...).
- **`libvec`** - a 3D vector algebra library (`dot`, `cross`, `normalize`,
  `reflect`, `lerp`, `clamp`...) used for every geometric computation.

-----

## Features

Everything below is currently implemented:

- **Scene parsing** - reads the `.rt` file passed as the first argument, checks
  the `.rt` extension, and parses the identifiers `A`, `C`, `L`, `sp`, `pl`, `cy`
  in any order. `A`, `C` and `L` are enforced to appear exactly once.
- **Validation** - ratios in `[0,1]`, colors in `[0,255]`, FOV in `[0,180]`.
  Any error prints `Error\n` followed by an explicit message and exits cleanly,
  with no leak.
- **MLX42 window** - opens a `1280x720` window and draws into an image buffer.
- **Camera** - builds the camera basis (`right` / `up` / `forward`) from the
  orientation vector and generates one primary ray per pixel according to the FOV.
- **Ray/object intersections**
  - **Sphere** - quadratic equation.
  - **Plane** - dot product.
  - **Cylinder** - bounded lateral surface **plus the two caps**.
- **Closest hit** - iterates over the object list and keeps the nearest positive
  intersection, then computes the surface normal at the impact point. The normal
  is flipped to face the incoming ray, so shading stays correct on both sides of
  a plane and inside spheres/cylinders.
- **Lighting (simplified Phong)** - each hit is shaded with an **ambient** term
  (so objects are never fully black) plus a **diffuse** (Lambert) term
  `max(0, N · L)` from the scene light, modulated by the object color and clamped
  to `[0,1]`.
- **Hard shadows** - a shadow ray is cast from the hit point towards the light;
  if an object stands strictly between them, the diffuse term is dropped and only
  the ambient term remains. The ray origin is nudged along the normal to avoid
  self-shadowing (shadow acne).
- **Rendering** - each hit pixel is filled with its shaded color; background
  pixels show a gradient based on the ray direction.
- **Interactive camera** - the camera can be moved along its own basis and
  rotated (yaw/pitch) from the keyboard, with a live re-render on each key.
- **Object selection & transforms** - `TAB` cycles through the scene objects,
  highlighting the current one. The selected object can be translated along the
  world axes, rotated (plane normal / cylinder axis, via Rodrigues' formula) and
  resized (radius, and height for a cylinder).
- **Adaptive render** - editing triggers a fast draft pass (one ray per 4×4
  block); the full-resolution pass runs once the input settles.

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
   Shading     →  ft_lighting  (ambient + diffuse + shadow ray)
                  (background gradient if no hit)
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

The scene is re-rendered live on every key press (and while a key is held, via
the keyboard auto-repeat).

**Camera** - moves along its own basis, rotates by `CAM_ROT_STEP` radians.

| Key       | Action                                                 |
|-----------|--------------------------------------------------------|
| `W` / `S` | Move forward / backward along the view direction       |
| `A` / `D` | Move left / right along the camera right axis          |
| `Q` / `E` | Move down / up along the camera up axis                |
| `←` / `→` | Yaw (rotate around the world up axis)                  |
| `↑` / `↓` | Pitch (rotate around the camera right axis)            |

**Selection**

| Key   | Action                                                             |
|-------|--------------------------------------------------------------------|
| `TAB` | Cycle to the next object in the scene (the selection is highlighted)|

**Selected object** - all the keys below act on the currently selected object,
so they do nothing until a first `TAB`.

| Key             | Action                                                    |
|-----------------|-----------------------------------------------------------|
| `J` / `L`       | Translate along the world **X** axis (-/+)                |
| `K` / `I`       | Translate along the world **Y** axis (-/+)                |
| `U` / `O`       | Translate along the world **Z** axis (-/+)                |
| `[` / `]`       | Rotate the axis around the world **X** axis (+/-)         |
| `;` / `'`       | Rotate the axis around the world **Y** axis (+/-)         |
| `+` / `-`       | Grow / shrink the radius (sphere, cylinder)               |
| `.` / `,`       | Grow / shrink the height (cylinder only)                  |

> **Note:** rotation only applies to objects that carry an orientation - the
> plane normal and the cylinder axis. A sphere has none, so it ignores those
> keys. Sizes are bounded below, so a radius or a height can never reach zero.
> `+` / `-` also work on the numeric keypad.

**Window**

| Key / action | Effect           |
|--------------|------------------|
| `ESC`        | Close the window |
| Window close | Close the window |

**Render quality while editing** - each edit triggers a *draft* render that
traces one ray per `RT_DRAFT_STEP × RT_DRAFT_STEP` pixel block (4×4 by default),
which keeps the interaction responsive. The full-quality pass (one ray per
pixel) is run `RT_REFINE_DELAY` seconds after the last edit, once every key is
released - with an `RT_REFINE_MAX` fallback so a missed release event can never
leave the image stuck at draft quality.

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
│   ├── render/         # Camera, primary rays, intersections, closest hit, lighting, transforms
│   ├── window/         # MLX42 window, event hooks, camera controls, object edition
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
- **Lighting** uses a simplified Phong model (ambient + diffuse). Colors are kept
  normalized in `[0,1]` throughout the pipeline, so light contributions combine
  by component-wise multiplication and are clamped once at the end.
- **Shadows** reuse the same intersection routines: a shadow ray is tested
  against every object and bounded by the distance to the light, with an
  `RT_EPSILON` offset along the normal to prevent shadow acne.
- **Error handling** always prints `Error\n` plus a message, frees the scene and
  exits without leaking.

-----

## Resources

Grouped by the mathematical notion they cover, with the part of the project
that relies on it.

### General references

- [MLX42 documentation](https://github.com/codam-coding-college/MLX42) - the
  windowing / image library used for the output.
- [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
  ([full series](https://raytracing.github.io/)) - the reference walkthrough:
  rays, spheres, normals, shading, cameras.
- [Scratchapixel](https://www.scratchapixel.com/) - lesson-based computer
  graphics maths, used throughout the sections below.
- [Ray casting (Wikipedia)](https://en.wikipedia.org/wiki/Ray_casting) and
  [Ray tracing (Wikipedia)](https://en.wikipedia.org/wiki/Ray_tracing_(graphics))
  - the overall algorithm this project implements.

### Vector algebra - `libvec`

- [Dot product](https://en.wikipedia.org/wiki/Dot_product) and
  [cross product](https://en.wikipedia.org/wiki/Cross_product) - behind
  `vec_dot` / `vec_cross`, used for every projection, angle and basis.
- [Unit vector](https://en.wikipedia.org/wiki/Unit_vector) - `vec_normalize`;
  ray directions and normals are kept unit-length so `N · L` is a cosine.
- [Vector projection](https://en.wikipedia.org/wiki/Vector_projection) - how a
  point is split into its along-axis and perpendicular parts, which is exactly
  what the cylinder height test and the cap tests do.
- [Scratchapixel - Math operations on points and vectors](https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/geometry/math-operations-on-points-and-vectors.html)
- [Linear interpolation](https://en.wikipedia.org/wiki/Linear_interpolation) -
  `vec_lerp`, used to blend the selected object's color towards white.

### Camera & primary rays - `srcs/render/camera.c`

- [Orthonormal basis](https://en.wikipedia.org/wiki/Orthonormal_basis) and the
  [Gram-Schmidt process](https://en.wikipedia.org/wiki/Gram%E2%80%93Schmidt_process)
  - building the `right` / `up` / `forward` triple from the single orientation
  vector given in the `.rt` file, and why a fallback world-up is needed when the
  camera looks straight up or down (degenerate cross product).
- [Scratchapixel - Generating camera rays](https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.html)
  - pixel → NDC → screen space, the `tan(fov/2)` scale and the aspect-ratio
  correction implemented in `ft_primary_ray`.
- [Field of view](https://en.wikipedia.org/wiki/Field_of_view_in_video_games) -
  the horizontal/vertical FOV relation and why the aspect ratio must be applied
  on a single axis.

### Ray/object intersection - `srcs/render/intersect*.c`

- [Line-sphere intersection](https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection)
  and [Scratchapixel - Ray-sphere intersection](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.html)
  - the geometric and the analytic (quadratic) solutions.
- [Quadratic formula](https://en.wikipedia.org/wiki/Quadratic_formula) and
  [loss of significance](https://en.wikipedia.org/wiki/Loss_of_significance) -
  reading the discriminant sign to count the roots, and the cancellation problem
  that makes the naive `(-b ± √Δ) / 2a` lose precision on grazing rays.
- [Line-plane intersection](https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection)
  and [Scratchapixel - Ray-plane and ray-disk intersection](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection.html)
  - the `t = (P₀ - O) · N / (D · N)` formula, the parallel case (`D · N ≈ 0`),
  and the disk test reused for the two cylinder caps.
- [Cylinder - implicit equation](https://en.wikipedia.org/wiki/Cylinder) and
  [quadric surfaces](https://en.wikipedia.org/wiki/Quadric) - the infinite
  cylinder as a quadric, which the axis-aligned distance test then clips to a
  finite height band.
- [Ray tracing primitives (University of Cambridge)](https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html)
  - the full derivation of the finite ray/cylinder intersection, caps included.
- [Inigo Quilez - Intersectors](https://iquilezles.org/articles/intersectors/) -
  compact, well-conditioned reference implementations to check the maths against.
- [Normal (geometry)](https://en.wikipedia.org/wiki/Normal_(geometry)) - the
  surface normal per primitive, and why it is flipped to face the incoming ray.

### Shading & shadows - `srcs/render/lighting.c`

- [Lambert's cosine law](https://en.wikipedia.org/wiki/Lambert%27s_cosine_law)
  and [Lambertian reflectance](https://en.wikipedia.org/wiki/Lambertian_reflectance)
  - the physical basis of the `max(0, N · L)` diffuse term.
- [Scratchapixel - Diffuse and Lambertian shading](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/diffuse-lambertian-shading.html)
- [Phong reflection model](https://en.wikipedia.org/wiki/Phong_reflection_model)
  and [Phong shading](https://en.wikipedia.org/wiki/Phong_shading) - the
  ambient + diffuse (+ specular) decomposition this project simplifies.
- [LearnOpenGL - Basic Lighting](https://learnopengl.com/Lighting/Basic-Lighting)
  - the same model derived step by step, with the vectors drawn out.
- [Scratchapixel - Shading normals](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/shading-normals.html)
- [Scratchapixel - Light and shadows](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/ligth-and-shadows.html)
  - shadow rays, and the shadow acne caused by floating-point error at the hit
  point (fixed here with the `RT_EPSILON` offset along the normal).
- [Shading (Wikipedia)](https://en.wikipedia.org/wiki/Shading) - the ambient
  term as a cheap stand-in for global illumination.

### Transformations - `srcs/render/transform.c`, `srcs/window/`

- [Rodrigues' rotation formula](https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula)
  - rotating a vector around an arbitrary axis without building a matrix; used
  for both the camera yaw/pitch and the object axis rotations.
- [Cross product](https://en.wikipedia.org/wiki/Cross_product) - the `k × v`
  term of that formula, and the handedness it fixes.

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

- **marudlof** - [codeberg.org/Vusk](https://codeberg.org/Vusk)
- **dakaymak**

*Built as part of the [42](https://42angouleme.fr/) curriculum.*
