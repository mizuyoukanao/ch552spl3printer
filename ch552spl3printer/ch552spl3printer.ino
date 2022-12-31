#include <CH55xSwitchControl.h>
#include "image.h"

int xpos = 0;
int ypos = 0;

void phat(uint8_t hat) {
    pressHatButton(hat);
    delay(32);
    releaseHatButton();
    delay(32);
}

void pushdot() {
    if (image[(xpos / 8) + (ypos * 40)] & 1 << (xpos % 8)) {
        pressButton(BUTTON_A);
        delay(32);
        releaseButton(BUTTON_A);
        delay(32);
    }
}

void setup() {
    USBInit();
    pushButtonLoop(BUTTON_A, 200, 10);
    pushButtonLoop(BUTTON_LCLICK, 100, 10);
    delay(500);
}

void loop() {
	if (ypos < 120) {
		if (ypos % 2) {
			pushdot();
			for ( xpos=318; xpos>=0; xpos-- ) {
				phat(HAT_LEFT);
				pushdot();
			}
            xpos = 0;
			for(int i=0;i<12;i++) phat(HAT_LEFT);
		} else {
			pushdot();
			for ( xpos=1; xpos<320; xpos++ ) {
				phat(HAT_RIGHT);
				pushdot();
			}
			for(int i=0;i<12;i++) phat(HAT_RIGHT);
		}
		phat(HAT_DOWN);
		ypos++;
	} else if (ypos == 120) {
		pressButton(BUTTON_MINUS);
        delay(32);
        releaseButton(BUTTON_MINUS);
        delay(32);
		ypos++;
	}
}
