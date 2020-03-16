# Lecture 1: Flappy Bird

## Important Functions

- `love.graphics.newImage(path)` - loads an image file from disk into an object that we can draw to the screen.
- `love.graphics.draw(object, x, y)

## Images (Sprites)

We want to draw a foreground and a background to the screen. We want both scrolling at different rates which is called parallax scrolling.

We put images in with `love.graphics.draw(background, 0, 0)`.

Parallax is the illusion of movement. Like IRL if you're driving and you see a fence moving really quickly up close, but a mountain far away doesn't appear to be moving.

## Infinite Scrolling

We set variables for the background and ground speed. We also want to set a looping point for the images. If we want this to work right we need to set our images up so that they look right when they loop.

## Games are Illusions

Trying to devise a scene that's very elaborate and doing it on constrained hardware. 

Colton recommends checking out the YouTube series Boundary Break.

Things like Death Mountain in OoT only being half rendered. Limited memory space means that the game devs wouldn't bother putting everything in when nobody would see it anyway.



## Procedural Generation

## State Machines

## Mouse Input

## Music

## Readings

<https://howtomakeanrpg.com>
<http://gameprogrammingpatterns.com>