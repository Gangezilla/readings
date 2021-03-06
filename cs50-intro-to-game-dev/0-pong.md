# Lecture 0 - Pong

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
- `love.window.setTitle(title)` will set a title on the application.
- `love.timer.getFPS()` will give us our FPS and we can see if we're performing well or poorly.
- `love.audio.newSource(path, [type])` will let us load some audio in.
- `love.resize(width, height)` which lets us resize the window.

Having different kinds of state.

## Classes

It's easier to do games with OO and classes. We can use a class to put all of our attributes and methods into a class and keep everything in the same spot.

Objects are instantiated from the class blueprint.
For pong, a paddle and ball are good use cases for this.

In these classes we have update and render functions in each class. We put the updates for the ball and render and call them individually. This way we can do a bunch of things in the update function a whole lot easier.

## Collision

Collision detection works on AABB collision detection. Axis-aligned bounding boxes which means collision boxes contain no rotation in our world space, allowing us to use a simple math formula to test for collision. Basically if opposite edges are on the opposite side of each other, we know that it's not colliding.

If the ball collides, we need to set it to it's negative value so it goes in the opposite x direction. 

## State Machine

A state machine is a ubiquitous concept in game development. How do we monitor what state we're in, and how do we handle this? Each individual state has different logic, and by breaking this logic out we can scale our code much easier. States are overall representation of a character's behaviour. We have a play state, serve state, game over state. You can define any arbitrary number of states, like, game over state, play state, high score state.

We talk about how to transition between different states, so like, play state transitions to serve state when someone loses a point.

It allows us to essentially have separate update functions within one update function. We'll eventually pull this out into a state machine class and be a bit more abstract about it but not right now.

## Sounds

Recommending a program called bfxr which lets you generate a bunch of random sounds, it's designed for small games like ours. It's pretty cool actually.

We load all of our sounds into a Lua table where we pass in keys and then some values generated by `love.audio.newSource`

```lua
sounds = {
  ['paddle_hit'] = love.audio.newSource('', 'static')
}
```

Static sounds are loaded in and kept in memory, we also have 'stream' which loads stuff on the fly which is good if we have tonnes of sounds and music.

## Resizing
