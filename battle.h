#ifndef BATTLE_H
#define BATTLE_H

#include "game.h"
#include <Arduino.h>

#ifdef __cplusplus
extern "C" {	/* Use C library with Arduino */
#endif

void battle_enemies(struct player *, struct enemy **);
void battle_enemy(struct player *, struct enemy *);

#ifdef __cplusplus
}
#endif

#endif
