#include "Map.h"
#include "TextureManager.h"
#include "GameObject.h"
#include <chrono>
#include <thread>
#include <iostream>

Map::Map(SDL_Renderer* renderer)
{
    grass = TextureManager::LoadTexture("assets/grass.png", renderer);
    field = TextureManager::LoadTexture("assets/field.png", renderer);
    road = TextureManager::LoadTexture("assets/road.png", renderer);
    stage0 = TextureManager::LoadTexture("assets/stage0.png", renderer);
    stage1 = TextureManager::LoadTexture("assets/stage1.png", renderer);
    stage2 = TextureManager::LoadTexture("assets/stage2.png", renderer);
    stage3 = TextureManager::LoadTexture("assets/stage3.png", renderer);
    wheat = TextureManager::LoadTexture("assets/wheat.png", renderer);
    oat = TextureManager::LoadTexture("assets/oat.png", renderer);
    corn = TextureManager::LoadTexture("assets/corn.png", renderer);

    int initialMap[20][25] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,2,2,2,2,2,2,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,2,2,2,2,2,2,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,2,2,2,2,2,2,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,2,2,2,2,2,2,0},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,1,1,1,1,2,2,2,2,2,0,1,1,1,1,1,1,1,1,0,0,0,0,0},
        {0,1,1,1,1,1,2,2,2,2,2,0,1,1,1,1,1,1,1,1,0,0,0,0,0},
        {0,1,1,1,1,1,2,2,2,2,2,0,1,1,1,1,1,1,1,1,0,0,0,0,0},
        {0,1,1,1,1,1,2,2,2,2,2,0,1,1,1,1,1,1,1,1,0,0,0,0,0},
        {0,0,0,0,0,0,2,2,2,2,2,0,1,1,1,1,1,1,1,1,0,0,0,0,0},
        {0,0,0,0,0,0,2,2,2,2,2,0,1,1,1,1,1,1,1,1,0,0,0,0,0},
        {0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    LoadMap(initialMap);

    src.x = src.y = 0;
    src.w = dest.w = 32;
    src.h = dest.h = 32;

    dest.x = dest.y = 0;
}

void Map::LoadMap(int arr[20][25])
{
    for (int row = 0; row < 20; row++)
    {
        for (int column = 0; column < 25; column++)
        {
            map[row][column] = arr[row][column];
        }
    }
}

void Map::DrawMap(SDL_Renderer* renderer)
{
    int type = 0;

    for (int row = 0; row < 20; row++)
    {
        for (int column = 0; column < 25; column++)
        {
            type = map[row][column];

            dest.x = column * 32;
            dest.y = row * 32;

            switch (type)
            {
            case 0:
                TextureManager::Draw(grass, src, dest, renderer);
                break;
            case 1:
                TextureManager::Draw(field, src, dest, renderer);
                break;
            case 2:
                TextureManager::Draw(road, src, dest, renderer);
                break;
            case 3:
                TextureManager::Draw(stage0, src, dest, renderer);
                break;
            case 4:
                TextureManager::Draw(stage1, src, dest, renderer);
                break;
            case 5:
                TextureManager::Draw(stage2, src, dest, renderer);
                break;
            case 6:
                TextureManager::Draw(stage3, src, dest, renderer);
                break;
            case 7:
                TextureManager::Draw(wheat, src, dest, renderer);
                break;
            case 8:
                TextureManager::Draw(oat, src, dest, renderer);
                break;
            case 9:
                TextureManager::Draw(corn, src, dest, renderer);
                break;
            default:
                break;
            }
        }
    }
}

bool Map::FieldColision(int posx, int posy, const char* type)
{
    int row = posy / 32;
    int column = posx / 32;

    if (map[row][column] == 1) {
        map[row][column] = 3;
        if (strcmp(type, "wheat") == 0) {
            uprawa.push_back(new Wheat(posx, posy));
        }
        else if (strcmp(type, "oat") == 0)
        {
            uprawa.push_back(new Oat(posx, posy));
        }
        else if (strcmp(type, "corn") == 0)
        {
            uprawa.push_back(new Corn(posx, posy));
        }

        
        uprawa[uprawa.size()-1]->xpos = posx;
        uprawa[uprawa.size() - 1]->ypos = posy;
        return true;
    }
    return false;
}

bool Map::Growing(int posx, int posy)
{
    int row = posy / 32;
    int column = posx / 32;
    for (int i = 0; i < uprawa.size(); i++) {
        int actualState = uprawa[i]->Growing();
        if (actualState != -1) {
            if (actualState != map[uprawa[i]->ypos / 32][uprawa[i]->xpos / 32]) {
                map[uprawa[i]->ypos / 32][uprawa[i]->xpos / 32] = actualState;
            }
        }
     
    }

    return true;
}

void Map::CheckForCoins(GameObject& player)
{
    int row = player.ypos / 32;
    int column = player.xpos / 32;

    if (map[row][column] == 7 || map[row][column] == 8 || map[row][column] == 9) {
        player.addCoins(1);
        map[row][column] = 0;
        std::cout << "Coins collected: " << player.getCoins() << std::endl;
    }
}

void Map::PlowField(int posx, int posy)
{
    int row = posy / 32;
    int column = posx / 32;

    if (map[row][column] == 0) {
        map[row][column] = 1;
        std::cout << "Field plowed!" << std::endl;
    }
}

int Map::Harvesting(int posx, int posy)
{
    int row = posy / 32;
    int column = posx / 32;

    if (row >= 0 && row < 20 && column >= 0 && column < 25) {
        if (map[row][column] == 7|| map[row][column] == 8|| map[row][column] == 9) {
            map[row][column] = 0;
        }
    }

    return 0;
}

