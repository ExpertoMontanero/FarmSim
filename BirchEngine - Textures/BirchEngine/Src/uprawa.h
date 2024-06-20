#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "string"

class Uprawa {
public:
	int xpos;
	int ypos;
	int stage=0;
	bool isGrown=false;
	SDL_Texture* texture;
	virtual int Growing()=0;

private:

};