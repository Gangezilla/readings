https://gabrielgambetta.com/computer-graphics-from-scratch/common-concepts.html

- We're drawing onto a canvas, which is a rectangular array of pixels that can be coloured individually. We'll build everything by painting a pixel with a color:
`canvas.PutPixel(x, y, color)`
- A canvas has a specific width and height in pixels. In most computer screens, the origin is the top left, x increases to the right and y increases down the screen. However we'll use one where the origin is in the center, x increases to the right and y increases up.
  - This means the range of x is [-Cw / 2, Cw / 2] and the range of y is [-Ch / 2, Ch / 2]

## Color Models
A color is what we call the way our brain interprets photons hitting the eyes. 
  
### Subtractive color model
This is fancy name for how you can scribble with a yellow crayon, then a blue crayon and it turns to green. This works basically by each colour absorbing certain wavelengths, which then leaves certain coloured wavelengths to be absorbed by our eyes.

The primary colours in this model are Cyan, Magenta, Yellow and Black. This is the CMYK model that printers, for example, use.

### Additive color model

Monitors are the opposite of paper because paper reflects light whereas monitors emit light. With paper we start with white light and subtract the wavelengths we don't want, whereas with a screen we start with no light and add the wavelengths we want. This is the RGB color model.

## Color depth and representation

How many colors can a screen make? The most common format to represent colors uses 8 bits per primary color (also called a color channel). This gives us 24 bits per pixel, which is 2^24 diff colors (16.7 million). This is known as 888 and we say that the format has a *color depth* of 24 bits.

## Color manipulation

- We can alter the intensity of a color by multiplying each color channel by a constant:
`k(R, G, B) = (kR, kG, kB)`
- We can add two colors together by adding the color channels separately:
`(R1, G1, B1) + (R2, G2, B2) = (R1 + R2, G1 + G2, B1 + B2)`

## The Scene

The canvas is the abstraction where you render the scene (which is another abstraction). The scene is the set of objects you may want to render, which could be whatever you want. To talk about this we need a coordinate system. In this case Y is up, X and Z are horizontal. So the plan XZ is the "floor", while XY and YZ are vertical "walls".