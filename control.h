#ifndef CONTROL_H
#define CONTROL_H

#ifdef __cplusplus
extern "C" {	/* Use C library with Arduino */
#endif

enum user_input {
	B_SELECT,
	B_CHANGE,
};

enum user_input get_user_input(void);
void debounce_button1(void);
void debounce_button2(void);

#ifdef __cplusplus
}
#endif

#endif
