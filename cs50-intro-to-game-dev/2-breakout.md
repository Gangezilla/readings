# Lecture 2 - Breakout

First thing we do is organise our game better by putting everything into proper folders instead of just dumping it all out.

We move all our constants into a constants file, and we put all of our fonts, graphics and sounds etc into their own table so we can access them a bit cleaner.

We also make a lib folder that contains all our deps, and also a Dependencies.lua file where we require everything so we can see at a glance what's been imported.

## Sprite Sheets

We use **quads** to define which sprites we want to pull out of our sprite sheet.

`love.graphics.newQuad(x, y, width, height, dimensions)`
`love.graphics.draw(texture, quad, x, y)`

## Procedural Layouts

## Managing State

## Levels

## Player Health

## Particle Systems

## Collision Detection Revisited

## Persistent Save Data