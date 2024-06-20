#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class GameObject {
public:
    GameObject(const char* texturesheet, int x, int y, SDL_Renderer* renderer);
    ~GameObject();

    void Update();
    void Render(SDL_Renderer* renderer);
    int getCoins() const;
    void setCoins(int coins);
    void addCoins(int amount);
    void removeCoins(int amount);

    SDL_RendererFlip flip;
    int direction_x;
    int direction_y;
    int xpos;
    int ypos;

    int seeder = 0;
    std::string selectedCrop;

private:
    int speed = 2;
    int coins;
    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
};
