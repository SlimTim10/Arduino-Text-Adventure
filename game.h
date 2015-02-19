#ifndef GAME_H
#define GAME_H

#ifdef __cplusplus
extern "C" {	/* Use C library with Arduino */
#endif

void setup_game(void);
void game_intro(void);
void next_dir_choice(void);
void travel(void);

#ifdef __cplusplus
}
#endif

#endif
