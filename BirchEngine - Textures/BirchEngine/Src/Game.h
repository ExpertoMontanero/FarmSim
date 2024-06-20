#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "GameObject.h"
#include "Map.h"

class Game
{
public:
    Game();
    ~Game();

    void init(const char* title, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    bool running() { return isRunning; }
    void render();
    void clean();

private:
    bool isRunning = false;
    SDL_Window* window;
    SDL_Renderer* renderer;

    GameObject* player;
    Map* map;

    const char* crops[5] = { "wheat", "corn", "oat", "plowing", "harvester" };
    int selectedCropIndex = 0;

    void printSelectedCrop();
};
