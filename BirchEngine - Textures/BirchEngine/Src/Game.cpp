#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include <iostream>

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }

        isRunning = true;
    }

    player = new GameObject("assets/tractor.png", 0, 0, renderer);
    player->selectedCrop = crops[selectedCropIndex];
    map = new Map(renderer);
    printSelectedCrop();
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_w) {
                player->direction_y = -1;
            }
            else if (event.key.keysym.sym == SDLK_s) {
                player->direction_y = 1;
            }
            else if (event.key.keysym.sym == SDLK_a) {
                player->direction_x = -1;
            }
            else if (event.key.keysym.sym == SDLK_d) {
                player->direction_x = 1;
            }
            else if (event.key.keysym.sym == SDLK_LEFT) {
                selectedCropIndex = (selectedCropIndex - 1 + 5) % 5;
                player->selectedCrop = crops[selectedCropIndex];
                printSelectedCrop();
            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                selectedCropIndex = (selectedCropIndex + 1) % 5;
                player->selectedCrop = crops[selectedCropIndex];
                printSelectedCrop();
            }
            break;
        case SDL_KEYUP:
            player->direction_x = 0;
            player->direction_y = 0;
            break;
        default:
            break;
        }
    }
}

void Game::update()
{
    player->Update();

    map->CheckForCoins(*player);

    if (player->selectedCrop == "plowing") {
        map->PlowField(player->xpos, player->ypos);
    }
    if (player->selectedCrop != "plowing" && player->selectedCrop != "harvester") {
        map->FieldColision(player->xpos, player->ypos, crops[selectedCropIndex]);
    }
    if (player->selectedCrop == "harvester") {
        map->Harvesting(player->xpos, player->ypos);
    }
    map->Growing(player->xpos, player->ypos);
}

void Game::render()
{
    SDL_RenderClear(renderer);
    map->DrawMap(renderer);
    player->Render(renderer);
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::printSelectedCrop()
{
    std::cout << "Selected crop: " << player->selectedCrop << std::endl;
}
