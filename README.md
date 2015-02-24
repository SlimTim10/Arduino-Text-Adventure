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

| Rooms | Rooms | Rooms | Rooms |
| :---: | :---: | :---: | :---: |
| [0,0] | [1,0] | [2,0] | [3,0]
| [0,1] | [1,1] | [2,1] | [3,1]
| [0,2] | [1,2] | [2,2] | [3,2]
| [0,3] | [1,3] | [2,3] | [3,3]

The map width and height can be customized (maximum 8 by 8). The text that accompanies each room is chosen at random from a set list of strings in the `resources` library.

#### Battle

The damage range when attacking is from `(attacker's level * 10) - ((attacker's level - opponent's level) * 10)` to `(attacker's level * 10) - ((attacker's level - opponent's level) * 10) + 10`. An attack of 0 damage is a miss. Damage cannot be negative.

For example: a level 3 player attacking a level 4 enemy can do 10 to 20 damage. A level 3 player attacking a level 3-or-below enemy can do 20 to 30 damage.

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

To customize the game, edit the `setup_world()` function in `arduinotextadventure.ino`.

* Set the map dimensions (maximum 8 by 8)

```
set_map_width(4);
set_map_height(4);
```

* Make walls (rooms that the player can't enter)

```
/* Make room [1,0] into a wall */
make_wall(1, 0);
/* Make room [2,2] into a wall */
make_wall(2, 2);
/* Make room [3,2] into a wall */
make_wall(3, 2);
```

* Add enemies (there can be at most 3 enemies in a room)

```
/* Add a level 1 snail to room [2,1] with 3 HP */
add_enemy(2, 1, "snail", 3, 1);
/* Add a level 1 rat to room [2,1] with 5 HP */
add_enemy(2, 1, "rat", 5, 1);
/* Add a level 4 Tim to room [2,3] with 20 HP */
add_enemy(2, 3, "Tim", 20, 4);
/* Add a level 5 Chris to room [2,3] with 30 HP */
add_enemy(2, 3, "Chris", 30, 5);
/* Add a level 10 David to room [3,3] with 20 HP */
add_enemy(3, 3, "David", 50, 10);
```

* Set up the player (starting location, HP, and level).

```
/* Start the player in room [0,0] with 100 HP and level 1 */
set_player_location(0, 0);
set_player_hp(100);
set_player_level(1);
```

## Notes

The strings in the `resources` library are stored in flash memory due to RAM being only 2 kB on the Arduino Uno. The following macro is for using the strings.

```
#define STR_TO_RAM(S)	(strcpy_P(str_buffer, S))
```

For example: `game_text(STR_TO_RAM(STR_WELCOME));`

For more information on using flash memory:
* http://www.gammon.com.au/progmem
* http://arduino.cc/en/Reference/PROGMEM