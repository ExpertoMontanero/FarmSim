#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, int x, int y, SDL_Renderer* renderer) : coins(0)
{
    objTexture = TextureManager::LoadTexture(texturesheet, renderer);
    xpos = x;
    ypos = y;
    flip = SDL_FLIP_NONE;
}

void GameObject::Update()
{
    if (direction_x == -1) {
        xpos -= speed;
    }
    else if (direction_x == 1) {
        xpos += speed;
    }
    if (direction_y == -1) {
        ypos -= speed;
    }
    else if (direction_y == 1) {
        ypos += speed;
    }

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;
    destRect.x = xpos;
    destRect.y = ypos - 16;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void GameObject::Render(SDL_Renderer* renderer)
{
    if (direction_x == 1) {
        flip = SDL_FLIP_HORIZONTAL;
    }
    else if (direction_x == -1) {
        flip = SDL_FLIP_NONE;
    }

    SDL_RenderCopyEx(renderer, objTexture, &srcRect, &destRect, 0, NULL, flip);
}

int GameObject::getCoins() const {
    return coins;
}

void GameObject::setCoins(int coins) {
    this->coins = coins;
}

void GameObject::addCoins(int amount) {
    coins += amount;
}

void GameObject::removeCoins(int amount) {
    coins -= amount;
}
