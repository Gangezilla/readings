# Light

The first step to add 'realism' to our scene will be the simluation of light. First, some simplifying assumptions:

- We declare that all light is white, which lets us characterise any light using a single number, i, or the *intensity* of the light.
  - Simulating colored light isn't that hard, you just use three intensity values, one per color channel, and compute all color and lighting channel-wise)
- We'll also ignore atmosphere, meaning lights don't become any less bright regardless of how far off they are. 

## Light sources

### Point lights

A point light emits light from a fixed point in space, its position. Light is emitted equally in every direction, so we call them omnidirectional lights. A lightbulb is a pretty reasonable approximation of this.

### Directional lights

Directional lights have an intensity, but they don't have a position. They instead have a direction.

### Ambient light

Most lights in real-life can be modeled as a point or directional light. Sometimes we need to use ambient light though. This means that when we shine light onto an object, sometimes it will absorb some light and scatter the rest of it onto the scene. This means we should treat every object as a light source, but it makes our model pretty complex so we won't worry about it right now.

Generally, a scene will have a single ambient light and an arbitrary number of point and directional lights

## Illumination of a single point

Generally a scene will have a single ambient light and an arbitrary number of point and directional lights.

In order to compute the illumination of a point, we'll just compute the amount of light contributed by each light source and add them together to get a single number representing the total amount of light it receives. We can then multiply the color of the surface at that point by this number to get the appropriately lit color.

## Diffuse reflection

When a ray of light hits a matte object, it's reflected back into the scene equally in every direction; diffuse reflection. This means the light you see reflected from the object is the same no matter where you're looking at the object from.

In order to decide what to do with this, we can classify objects as matte or shiny. This happens because the energy carried by the ray has to spread over a smaller or bigger area depending on the angle, so the energy reflected to the scene per unit of area is higher or lower.


### Modeling diffuse reflection

When a ray of light hits a surface, what fraction of that light's intensity is reflected back to the scene?

Lots of maths to derive an equation that we can use to compute the full amount of light received by a point in a scene.

We refer to the point that gets hit as a "normal", and its essentially a perpendicular line rising from the surface of our sphere. For a sphere, the normal vector lies on a line that goes through the center of the sphere. 