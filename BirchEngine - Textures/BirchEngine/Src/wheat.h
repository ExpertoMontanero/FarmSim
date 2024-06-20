#pragma once
#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "uprawa.h"
#include <string>
using namespace std;
class Wheat :public Uprawa{

public:
	
	int xpos;
	int ypos;
	int counter = 0;
	int stage = 0;
	SDL_Texture* texture;
	int Growing();

	Wheat(int x, int y);

private:

};