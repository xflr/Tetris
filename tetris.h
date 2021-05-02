#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 768;
const int gridWidth = 15;
const int gridHeight = 24;
const int TILE_SIZE = 32;

struct grid
{
    SDL_Color color;
    bool matrix[gridHeight][gridWidth];
    double x, y;
};

grid stage
{
    {0,255,128},{ //U format stage boundaries grid
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},
    0,0
}, curGrid;



struct shape
{
    SDL_Color color;
    bool matrix[4][4];
    double x, y;
    int size;
};

shape blocks[7] 
{
    {
        {255,255,0},{ //L BLOCK
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}},
        5,0,3
    },
    {
        {255,130,0},{ //I BLOCK
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}},
        5,0,4
    },
    {
        {230,125,180},{ //Z BLOCK
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}},
        5,0,3
    },
    {
        {230,50,255},{ //J BLOCK
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}},
        5,0,3
    },
    {
        {0,255,128},{ //SQUARE BLOCK
        {1,1,0,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}},
        5,0,2
    },
    {
        {0,48,128},{ //S BLOCK
        {0,0,0,0},
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0}},
        5,0,3
    },
    {
        {0,255,128},{ //T BLOCK
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}},
        5,0,3
    }
}, cur;
