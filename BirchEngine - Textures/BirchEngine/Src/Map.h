#pragma once

#include "SDL.h"
#include "GameObject.h"
#include <vector>
#include "uprawa.h"
#include "wheat.h"
#include "oat.h"
#include "corn.h"

using namespace std;
class Map
{
public:
    Map(SDL_Renderer* renderer);
    ~Map();

    void LoadMap(int arr[20][25]);
    void DrawMap(SDL_Renderer* renderer);
    bool FieldColision(int posx, int posy,const char* type);
    int Harvesting(int posx, int posy);
    bool Growing(int posx, int posy);
    void CheckForCoins(GameObject& player);
    void PlowField(int posx, int posy);

private:
    SDL_Rect src, dest;
    SDL_Texture* grass;
    SDL_Texture* field;
    SDL_Texture* road;
    SDL_Texture* stage0;
    SDL_Texture* stage1;
    SDL_Texture* stage2;
    SDL_Texture* stage3;
    SDL_Texture* wheat;
    SDL_Texture* oat;
    SDL_Texture* corn;
    
    vector <Uprawa*> uprawa;
    int map[20][25];
};
