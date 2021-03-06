# Arduino Text Adventure

## Description

[Animated example](http://i.imgur.com/UUFMrrV.gif)

A text adventure game for the Arduino Uno. The goal is to reach a specific room in the map.

#### Controls

| Input | Function |
| :--- | :--- |
| Button 1 | Move cursor |
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

#### Battle System

The damage range when attacking is from `(attacker's level * 10) - ((attacker's level - opponent's level) * 10)` to `(attacker's level * 10) - ((attacker's level - opponent's level) * 10) + 10`. In other words, the damage range is from `(attacker's level - 10) * 10` to `attacker's level * 10` minus 10 for every level the opponent is higher than the attacker.

An attack of 0 damage is a miss. Damage cannot be negative.

Examples:

* A level 1 player and a level 1 enemy can do 0 to 10 damage to each other.
* A level 3 player attacking a level 3-or-below enemy can do 20 to 30 damage.
* A level 3 player attacking a level 4 enemy can do 10 to 20 damage. The enemy can do 30 to 40 damage.

When a battle is won, the player gains XP (experience) equal to `enemy's level * 10`. The player becomes level 2 when their XP reaches 20. For each subsequent level, the required XP increases by `player's level * 10 * 2`. The maximum level is 10 (for enemies too).

## Hardware

- [Arduino Uno](http://arduino.cc/en/Main/arduinoBoardUno)
- [Nokia 5110 LCD](https://www.sparkfun.com/products/10168)
  - [Datasheet](http://www.sparkfun.com/datasheets/LCD/Monochrome/Nokia5110.pdf)
  - [Sample Code](http://playground.arduino.cc/Code/PCD8544)
- 2 Pushbuttons
- Potentiometer

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

To customize the game, edit the `setup_world()` function in `arduinotextadventure.ino`. You can set the map dimensions, set the goal location, make walls, add enemies, and set up the player.

Example:

```C
void setup_world(void) {
	/* Set map dimensions (maximum 8 by 8) */
	set_map_width(4);
	set_map_height(4);

	/* Set the goal at [3,3] */
	set_goal(3, 3);

	/* Map */
	/* [0,0] [1,0] [2,0] [3,0] */
	/* [0,1] [1,1] [2,1] [3,1]  */
	/* [0,2] [1,2] [2,2] [3,2] */
	/* [0,3] [1,3] [2,3] [3,3] */

	/* Make room [1,0] into a wall (player can't enter this room) */
	make_wall(1, 0);
	/* Make room [2,2] into a wall */
	make_wall(2, 2);
	/* Make room [3,2] into a wall */
	make_wall(3, 2);

	/* There can be at most 3 enemies in a room */
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

	/* Start the player in room [0,0] */
	set_player_location(0, 0);

	/* Player's starting HP and level */
	set_player_hp(100);
	set_player_level(1);
}
```

## Notes

#### LCD Library

This project is bundled with the [PCD8544 library](https://github.com/Icewire-Makerspace/PCD8544).

#### Resource Strings

The strings in the `resources` library are stored in flash memory due to RAM being only 2 kB on the Arduino Uno. The following macro is for using the strings.

```C
#define STR_TO_RAM(S)	(strcpy_P(str_buffer, S))
```

For example: `game_text(STR_TO_RAM(STR_WELCOME));`

For more information on using flash memory:
* http://www.gammon.com.au/progmem
* http://arduino.cc/en/Reference/PROGMEM