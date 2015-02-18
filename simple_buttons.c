#include "simple_buttons.h"

/*
  Arduino Uno external interrupts:
  Pin 2: int_0
  Pin 3: int_1
*/

enum constants {
	DEBOUNCE_MS = 20,
};

volatile boolean *d2flag = false;
volatile boolean *d3flag = false;

/* Set flag to true when interrupt on external pin is triggered */
void simple_interrupt(uint8_t pin, uint8_t trig, volatile void *flag) {
	switch (pin) {
	case 2:
		/* D2 */
		d2flag = flag;
		EIFR &= ~bit(INTF0);	/* Clear D2 interrupt flag */
		switch (trig) {
		case LOW:
			EICRA &= ~bit(ISC00);	/* Trigger on low */
			EICRA &= ~bit(ISC01);
			break;
		case CHANGE:
			EICRA |= bit(ISC00);	/* Trigger on change */
			EICRA &= ~bit(ISC01);
			break;
		case FALLING:
			EICRA &= ~bit(ISC00);
			EICRA |= bit(ISC01);	/* Trigger on falling edge */
			break;
		case RISING:
			EICRA |= bit(ISC00) | bit(ISC01);	/* Trigger on rising edge */
			break;
		}
		EIMSK |= bit(INT0);	/* Enable INT0 interrupt */
		break;
	case 3:
		/* D3 */
		d3flag = flag;
		EIFR &= ~bit(INTF1);	/* Clear D3 interrupt flag */
		switch (trig) {
		case LOW:
			EICRA &= ~bit(ISC10);	/* Trigger on low */
			EICRA &= ~bit(ISC11);
			break;
		case CHANGE:
			EICRA |= bit(ISC10);	/* Trigger on change */
			EICRA &= ~bit(ISC11);
			break;
		case FALLING:
			EICRA &= ~bit(ISC10);
			EICRA |= bit(ISC11);	/* Trigger on falling edge */
			break;
		case RISING:
			EICRA |= bit(ISC10) | bit(ISC11);	/* Trigger on rising edge */
			break;
		}
		EIMSK |= bit(INT1);	/* Enable INT0 interrupt */
		break;
	default:
		return;
	}

	/* Enable interrupts */
	interrupts();
}

/* Debounce and wait until button has settled at the desired state */
void simple_debounce(uint8_t pin, boolean state) {
	delay(DEBOUNCE_MS);
	while (digitalRead(pin) != state);
}

ISR(INT0_vect) {
	*d2flag = true;
}

ISR(INT1_vect) {
	*d3flag = true;
}
