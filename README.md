# a500kbd-usbhid-stm32

This is a firmware for a cheap STM32F103C6T8 microcontroller that allows you to use an original Commodore Amiga keyboard as USB HID device. The HAL middleware has been created with STM32CubeMX, protocol has been implemented according original Amiga Hardware Reference Manual which describes the handshake pretty straight forward.

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
