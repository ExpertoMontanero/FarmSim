#include "oat.h"

int Oat::Growing() {
	if (isGrown == false) {
		counter++;
		if (counter >= 500) {
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
				return 8;
				isGrown = true;
			}
		}
		return -1;
	}
}
Oat::Oat(int x, int y) {
	xpos = x;
	ypos = y;
}