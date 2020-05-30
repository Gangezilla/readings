# Notes

Plugging the dongle in brings up a new device in `dev/` called `/dev/tty.SLAB_USBtoUART`. Pretty neat in that dev folder actually.

Running `screen /dev/tty.SLAB_USBtoUART 115200` lets us use `screen` which is a serieal console emulator that connects to CP2102 and shows us whats being sent over the wire.

## Phase 2: GPIO

GPIO: General Purpose I/O. A GPIO pin can act as either output or input. When it's output, it can be either on or off. When its on, the RPI drives the pin at 3.3V

## Phase 3: Shining C

The vast majority of modern hardware devices comunicate with software through *memory-mapped I/O*. This means that devices expose their functionality through the machine's memory and provide a spec about what will happen if certain address are read or written to. These addresses are either 32 or 64 bit registers. We know which registers a device exposes, where in memory they're mapped and what they do from data sheets.

### GPFSELn

[Reference sheet]<https://cs140e.sergio.bz/docs/BCM2837-ARM-Peripherals.pdf> p91 + 92

GPIO function select regisers. The function select registers are used to define the operation of the GPIO pins. Each of the 54 GPIO pins has at least two alternative functions. We write to this register to set up a pin as an output or input.

For phase 3 we only care about three registers:

| Name | Peripheral Address | Description | Size | R/W |
|------| ------------------ | ----------- | ---- | --- |
|GPFSEL1| 0x7E200004      | GPIO func sel 1 | 32 bits | R/W |
|GPSET0|0x7e20001C        | GPIO Pin Out Set 0 | 32bits | W |
|GPCLR0 | 0x7E200028      | GPIO Pin clear 0   | 32 bits | W |

#### Which value to which field in register `GPFSEL1` must be written so that GPIO pin 16 is set as an output?

The `FSEL{n}` field determines the functionality of the nth GPIO pin.

#### Which value do we write to which field in these registers to set/clear pin 16?

We write to `GPSET0` to set a pin (turn it on) and `GPCLR0` to clear a pin (turn it off). on p95 of the spec sheet: The otput set registers are used to set a GPIO pin. The `SET{n}` field defins the respective GPIO pin to set. 
