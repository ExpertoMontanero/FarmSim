#include "wheat.h"

int Wheat::Growing() {
	if (isGrown == false) {
	counter++;
	if (counter >= 250) {
		counter = 0;
		stage++;
		if (stage==1) {
			return 4;
		}
		else if (stage == 2) {
			return 5;
		}
		else if (stage == 3) {
			return 6;
		}
		else if (stage == 4) {
			return 7;
			isGrown = true;
		}
	}
	return -1;
	}
}
Wheat::Wheat(int x, int y) {
	xpos = x;
	ypos = y;
}