# Raytracing

A computer is essentially a very methodical machine absolutely lacking artistic talent. It basically goes:

```pseudocode
For each pixel on the canvas
  Paint it with the right color
```

But we'd want a few more details:

```pseudocode
Place the eye and the frame as desired
For each pixel on the canvas
  Determine the square on the grid corresponding to this pixel
  Determine the color seen through that square
  Paint the pixel with that color
```

## Basic assumptions

- First we'll assume a fixed viewing position. A viewing position is the place where you'd put the eye, usually called the camera position, which we'll call `O = (Ox, Oy, Oz)`. We'll assume the camera is located at the origin of the coordinate system, so O = (0, 0, 0). 
- Second, we'll also assume a fixed camera orientation, with the camera looking down the Z axis, and positive X axis up, and positive X axis to the right.
- The rectangle that will act as our window to the world is called the viewport. Essentially, we draw on the canvas whatever we would see through that viewport. Note that the size of the viewport and the distance to the camera determine the angle visible from the camera, called the FOV.
What we do is trace the rays "in reverse", where we start with a ray originating from the camera, going through a point in the viewport and following it until it hits some object in the scene. 

## Canvas to Viewport

We place the viewport so its axes match the orientation of the canvas, and its center matches the center of the canas. Cos the viewport is measured in world units, and the canvas is measured in pixels, going from one to the other is just a change of scale.

## Tracing Rays

We will consider the rays of light in reverse by starting with a ray originating from the camera, going through a point in the viewport and tracing its path until it hits some object in the scene. This object is what the camera sees through that point of the viewport.

## The ray equation

The best way to represent rays for our purpose is using a parametric equation. We know the ray passes through O and we know it's direction (O to V), so we can express any point P in the ray as `P = O + t(V - O)` where t is an arbitrary real number.

Let's call (V - O) the direction of the ray, then the equation becomes simply `P = O + tD`. You can understand this as us starting the ray at the origin, and advancing along the direction of the ray (D) by some amount (t).

### The sphere equation

We use spheres cos they're easy to manipulate with equations.

A sphere is the set of points that lie at a fixed distance (the radius) from a fixed point (the center). If C is the center and r is the radius of the sphere, the points P on the surface satisfy the following equation: `<P - C, P - C> = r^2`

Do the ray and the sphere intersect? If so, where?

Lots of equation derivation leads to a classic quadratic equation.

## Rendering our first spheres

For each pixel on the canvas, we can compute the corresponding point on the viewport. Given the position of the camera, we can express the equation of a ray that starts at the camera and goes through that point of the viewport.