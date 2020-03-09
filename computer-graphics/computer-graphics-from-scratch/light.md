# Light

The first step to add 'realism' to our scene will be the simluation of light. First, some simplifying assumptions:

- We declare that all light is white, which lets us characterise any light using a single number, i, or the *intensity* of the light.
  - Simulating colored light isn't that hard, you just use three intensity values, one per color channel, and compute all color and lighting channel-wise)
- We'll also ignore atmosphere, meaning lights don't become any less bright regardless of how far off they are. 

## Light sources

### Point lights

A point light emits light from a fixed point in space, its position. Light is emitted equally in every direction, so we call them omnidirectional lights.

### Directional lights

Directional lights have an intensity, but they don't have a position. They instead have a direction.

### Ambient light

Most lights in real-life can be modeled as a point or directional light. Sometimes we need to use ambient light though. This means that when we shine light onto an object, sometimes it will absorb some light and scatter the rest of it onto the scene. This means we should treat every object as a light source, but it makes our model pretty complex so we won't worry about it right now.

## Illumination of a single point

Generally a scene will have a single ambient light and an arbitrary number of point and directional lights.

In order to compute the illumination of a point, we'll just compute the amount of light contributed by each light source and add them together to get a single number representing the total amount of light it receives. We can then multiply the color of the surface at that point by this number to get the appropriately lit color.

In order to decide what to do with this, we can classify objects as matte or shiny. 

## Diffuse reflection

When a ray of light hits a matte object, it's reflected back into the scene equally in every direction; diffuse reflection. This means the light you see reflected from the object is the same no matter where you're looking at the object from.

### Modeling diffuse reflection

When a ray of light hits a surface, what faction of that light's intensity is reflected back to the scene?
