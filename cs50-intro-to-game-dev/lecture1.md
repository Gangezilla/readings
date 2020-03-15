# Lecture 1 - Pong

## Lua (Portugese for moon)

Flexible lightweight scripting language, very popular in the video game industry, quite similar to JS (wahoo!)

Almost everything in Lua is a table, which is essentially an object in JS. Perfect for interacting with game engines. We use Lua with a compiled game engine, Love2D.

## Love2D

Uses Lua as its game engine, has a bunch of modules built in. Totally free and portable, great for prototyping.

## What's a game loop?

A game fundamentally is an infinite loop where every iteration we do a set of steps. We process input, we update the game, then we render.

## 2D Coordinate System

Origin is top left, y increases down, x increases right.

## Important functions

- `love.load()` is used for initialising our game state at the beginning of program execution. We overwrite love.load with whatever we want to happen
- `love.update(dt)` gets called each frame by LOVE. `dt` will be the elapsed time in seconds since the last frame, and we can use this to scale any changes in our game for even behaviour.
- `love.draw()` gets called each frame by LOVE after update for drawing things to the screen once they've changed.
- `love.graphics.printf(text, x, y, width, align)` lets us draw text to the screen
- `love.window.setMode(width, height, params)` is used to initialise the window's dimensions and set graphics options params
- `love.graphics.setDefaultFilter(min, mag)` sets the texture scaling and lets us change how stuff looks
- `love.keypress(key)` lets us deal with key presses.
- `love.event.quit()`
- `love.graphics.newFont(path, size)` will take a path to a font size and set it to an object that we can use to globally change the font.
- `love.graphics.setFont(font)` will take the font object we've defined in the above font and then set LOVE2D to use that font.
- `love.graphics.clear(r, g, b, a)` will wipe the screen with that color.
- `love.graphics.rectangle(mode, x, y, width, height)` draws a rectangle onto the screen using whichever our active color is.
- `love.keyboard.isDown(key)`
- `math.randomseed(num)` gives the random numbers a starting value to begin with. 
- `os.time()` returns time. It's used very commonly as a seed, because it's gonna be a really high number based off the Unix epoch
- `math.random(min, max)`
- `math.min(num1, num2)`
- `math.max(num1, num2)`

Having different kinds of state.

## Classes

It's easier to do games with OO and classes. We can use a class to put all of our attributes and methods into a class and keep everything in the same spot.

Objects are instantiated from the class blueprint.
For pong, a paddle and ball are good use cases for this.