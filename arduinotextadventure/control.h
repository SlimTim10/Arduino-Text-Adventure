#ifndef CONTROL_H
#define CONTROL_H

#ifdef __cplusplus
extern "C" {	/* Use C library with Arduino */
#endif

enum user_input {
	B_NONE,
	B_SELECT,
	B_CHANGE,
};

void setup_control(void);
enum user_input get_user_input(void);
void button1_wait(void);
void button2_wait(void);

#ifdef __cplusplus
}
#endif

#endif
