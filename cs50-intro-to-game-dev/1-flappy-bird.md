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

## Bird

### Init

We have a sprite and we get the width from `self.image:getWidth()`.

We also put the x of the image as the width / 2

### Render

`love.graphics.draw()`. Then in the main file we `require 'Bird'` then we can just call `bird.render()` in the main draw function

### Gravity

We use `dy` with a fixed gravity value. We can set our initial velocity to 0 and apply this velocity to the bird.

### Update

We'll be passing in a `dt` value. `self.dy = self.dy + GRAVITY * dt`

### Controls

`love.keyboard.keysPressed = {}` `love.keyboard` is a table and we're adding our own values into it. Then in the `love.keypressed` function we're adding a pressed key to this table.

We do all this work of keeping track of all our inputs so we can check which keys are being pressed outside of `main.lua`

## Procedural Generation

For memory purposes we want to destroy the pipes as we build them.

## Pipe

We want to make a Pipe class. We don't wanna make it have a lot of data, but it needs some. We load an image in the class cos it would be too inefficient to load an image independently.

We set a scroll value to be a negative number so it moves to the left. Interesting because the bird doesn't move, the pipes do. That's always a bit different to what I had assumed happened.

We set it's x to the VIRTUAL_WIDTH so when it spawns it comes from the far right.

We have an update function and we increase their x with our scroll distance every time we update.

We create a variable called `spawnTimer` and we check if it's over a certain number like 2 seconds for instance and if its greater than 2 we want to add a new pipe like `table.insert(pipes, Pipe())` we also want to now reset the spawnTimer to 0 otherwise it would spawn new pipes every frame lol. 

If we want to iterate over a table we can iterate over a table like `for k, pipe in pairs(pipes) do` it looks very Golang. In here we update each pipe! We also need to remove each pipe from here too. We do this by checking if each pipe.x is less than -pipe.width because if we did 0 we'd see the disappear. We remove like `table.remove(pipes, pipe)`

It's important that we draw the pipes FIRST and then the ground, so that they appear in front of the ground. We do the background before this, otherwise it would sit on top of everything.

## PipePair

Pipes come in pairs and they get shifted from the spawn zone (on right) to dead zone (on left). We create a new `PipePair` class which represents pairs of pipes together.

We have a new variables called `lastY` which will allow us to make the pipes passable, otherwise if it was totally random then it would be impossible. We write some code so that our pipe will be flipped up.

We instantiate a pipe pair with the top being self.y, and the bottom one being self.y + PIPE_HEIGHT + GAP_HEIGHT.

We also defer the render of each PipePair to the pipe function so they all update the same.

When you scale a sprite to -1, it flips it on the axis that you've scaled it.

## Collision

When we calculate collision we're basically shrinking the box so we subtract a little bit away. We do this to add a bit of leeway because we want to make the game more fun and a bit less stressful. Not heaps, just a few pixels to make the game more forgiving and fun.

## State Machines

We want a screen that lets us play through the game, and we want one to count us down. He's done a state flow which is pretty neat, probably good to do in the future.

We use a lowercase 'g' to indicate that something is global.

We then can use `gStateMachine:change('title')` and that'll change it to what we specify. We can call `gStateMachine:update(dt)` and it'll look at what our current state is and then use the logic in there to update it.

BaseState implements empty methods and we extend this so that we can avoid lots of boilerplate basically.

## Score

This is a new state.

We add a new bool to the pipe and when we remove that pipe then we update the score if that boolean is set.

## Countdown

Once again, a new state. 

Just doing a timer, and decrementing and displaying that timer. When the timer gets to be 0, we change the state to the play state.

## Mouse Input

`love.mousepressed(x, y, button)` gets fired everytime a mouse button is pressed, also gives you the X and Y coords too.

## Music

We initialise a table of sounds with different keys, including the bg music. We start the music by going `sounds['music']:setLooping(true)` to make it loop.

Then when we make the bird jump we make it play a certain sound, we do the same when we score a point etc. We can also layer sounds and make them play at the same time. I wonder how doing them together is executed.

Side note, music really makes it all come together omg. It goes from 'cool' to 'wow thats awesome'.

## Readings

<https://howtomakeanrpg.com>
<http://gameprogrammingpatterns.com>