#include "corn.h"

int Corn::Growing() {
	if (isGrown == false) {
		counter++;
		if (counter >= 750) {
			counter = 0;
			stage++;
			if (stage == 1) {
				return 4;
			}
			else if (stage == 2) {
				return 5;
			}
			else if (stage == 3) {
				return 6;
			}
			else if (stage == 4) {
				return 9;
				isGrown = true;
			}
		}
		return -1;
	}
}
Corn::Corn(int x, int y) {
	xpos = x;
	ypos = y;
}