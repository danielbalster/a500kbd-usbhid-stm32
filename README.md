# a500kbd-usbhid-stm32

*warning: still needs a big cleanup and better documentation*

This is a firmware for a cheap STM32F103C6T8 microcontroller that allows you to use an original Commodore Amiga keyboard as USB HID device. The HAL middleware has been created with STM32CubeMX, protocol has been implemented according original Amiga Hardware Reference Manual which describes the handshake pretty straight forward.

# Ideas #

### support the Amiga keyboard LEDs through HID output report
my STM32 is not strong enough to drive the LEDs and would require some extra circuitry. Or, I'm adding a few more modern LEDs and colors

### embedded virtual serial port
this would allow an always available serial console for the keyboard and no extra cables. User would just open the new COM port and could see debug messages and configure it, ie a text console with configuration commands

### add a motion processing unit
they're also cheap and suddenly the keyboard has accelleration, magnetoscope, gyroscope, ... and you could swing it like a sword game controller...

### cat lock, not caps lock.
I don't have a cat, but some magic keystroke should allow you to completely ignore all input - except the magic unlock keystroke. Or even as a child/baby protection: slurp all keys that would do something bad like reset, windows key, alt-tab, etc - then your kid could type whatever it wants but no accidental exits any more

### 

Here's a picture of the custom layout of my german A500 keyboard:

![a500 layout](a500-german-keyboard-layout.png)

## Mouse mode
You can enter USB mouse mode by pressing Help-m. Now the *Del* and *Help* key become left and right mouse buttons, the cursor keys allow you to steer you pointer.
- *Keypad Minus* will decrease pointer speed
- *Keypad Plus* will increase pointer speed
- *Keypad Multiply* will leave mouse mode

## Extended Function Keys
By pressing Help-<function key> you will have function keys F11 to F20. Alternate function can be toggled with Help-Del, then you will have the media keys as displayed in the image:
  - F1 : rewind
  - F2 : stop
  - F3 : pause/play
  - F4 : forward
  - F5 : eject
  - F8 : mute volume
  - F9 : decrease volume
  - F10 : increase volume

## Swap Alt and Ctrl
Pressing Help-LeftAlt will remap Modifier keys:
- Left Ctrl becomes Left Alt
- Left Alt becomes Left Control
- Right Amiga becomes Alt Gr
- Right Alt becomes Right Control
Pressing Help-Ctrl will return to original labelling.

## Miscellaneous
- CAPS lock is not implemented, I'm not using that key anyway
- you can ctrl-amiga-amiga (softreset) the keyboard
- USB vid/pid are pure fantasy (6666:6666)

# How to build and assemble

- Get your favorite STM32 microcontroller. I'm using a very cheap STM32F103C6T8 development board for less than $2
- connect DATA, CLOCK, RESET, 5V and GND with the microcontroller. 
- everything is done in main.c and survives a re-generation using the STM32CubeMX code generator, but there are two modifications in the code that will be overwritten:
1) usbd_hid.c:USBD_HID_SendReport() has been changed to actually return the success state
2) HID_CUSTOM_ReportDesc has been changed to mouse+keyboard descriptor




