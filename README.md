# Arduino Text Adventure

## Description

A text adventure game for the Arduino Uno.

#### Controls

| Input | Function |
| :--- | :--- |
| Button 1 | Change selection |
| Button 2 | Make selection |
| Potentiometer | Change LCD contrast (only works while waiting for button press) |

#### Map

| [0,0] | [1,0] | [2,0] | [3,0] |
| [0,1] | [1,1] | [2,1] | [3,1] |
| [0,2] | [1,2] | [2,2] | [3,2] |
| [0,3] | [1,3] | [2,3] | [3,3] |

The text that accompanies each room is chosen at random from a set list of strings in the `resources` library.

## Hardware

- [Arduino Uno](http://arduino.cc/en/Main/arduinoBoardUno)
- [Nokia 5110 LCD](https://www.sparkfun.com/products/10168)
  - [Datasheet](http://www.sparkfun.com/datasheets/LCD/Monochrome/Nokia5110.pdf)
  - [Sample Code](http://playground.arduino.cc/Code/PCD8544)

## Pinout

| Arduino Uno | Nokia 5110 LCD Breakout |
| ---: | :--- |
| Digital 6 | 1 (RST) |
| Digital 7 | 2 (CE) |
| Digital 5 | 3 (DC) |
| Digital 4 | 4 (DIN) |
| Digital 8 | 5 (CLK) |
| 5V | 6 (VCC) |
| Digital 9 | 7 (LIGHT) |
| GND | 8 (GND) |

| Arduino Uno | Buttons (pull-down) |
| ---: | :--- |
| Digital 2 | Button 1 (CHANGE) |
| Digital 3 | Button 2 (SELECT) |

| Arduino Uno | Potentiometer |
| ---: | :--- |
| Analog 0 | Potentiometer |

## Development

To customize the game, edit the `setup_world()` function in `arduinotextadventure.ino`. You can make walls, add enemies, and set up the player (starting location, HP, and level).

## Notes

The strings in the `resources` library are stored in flash memory due to RAM being only 2 kB on the Arduino Uno. The following macro is for using the strings

```
#define STR_TO_RAM(S)	(strcpy_P(str_buffer, S))
```

For example: `game_text(STR_TO_RAM(STR_WELCOME));`

For more information:
* http://www.gammon.com.au/progmem
* http://arduino.cc/en/Reference/PROGMEM