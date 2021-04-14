#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

wstring tetromino[7];

int nFieldWidth = 12; //game field width
int nFieldHeight = 18; //game field height
unsigned char *pField = nullptr; //initiate field as null pointer

int nScreenWidth = 80;
int nScreenHeight = 30;

int Rotate(int px, int py, int r)
{
    switch (r % 4)
    {
    case 0: return py * 4 + px; // no rotation
    case 1: return 12 + py - (px *4);   //rotating the tetromino matrix by 90 degrees.
    case 2: return 15 - (py * 4) - px;  //rotating the tetromino matrix by 180 degrees.
    case 3: return 3 - py + (px * 4);   //rotating the tetromino matrix by 270 degrees.
    }           
    return 0;
}

int main ( int argc, char* args[] )
{
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    if ( SDL_Init ( SDL_INIT_VIDEO ) < 0)
    {
        printf( "SDL coud not intilalize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        window = SDL_CreateWindow( "TETRIS by Alexandre Bressane", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    
        if( window == NULL )
            {
                printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            }

            else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            
            //Update the surface
            SDL_UpdateWindowSurface( window );

            //Wait two seconds
            SDL_Delay( 2000 );
        }
    }

    //tetris blocks as assets in tetromino matrix
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");

    tetromino[1].append(L"..X.");
    tetromino[1].append(L".XX.");
    tetromino[1].append(L".X..");
    tetromino[1].append(L"....");

    tetromino[2].append(L".X..");
    tetromino[2].append(L".XX.");
    tetromino[2].append(L"..X.");
    tetromino[2].append(L"....");
    
    tetromino[3].append(L"....");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L"....");

    tetromino[4].append(L"..X.");
    tetromino[4].append(L".XX.");
    tetromino[4].append(L"..X.");
    tetromino[4].append(L"....");

    tetromino[5].append(L"....");
    tetromino[5].append(L".XX.");
    tetromino[5].append(L"..X.");
    tetromino[5].append(L"..X.");

    tetromino[6].append(L"....");
    tetromino[6].append(L".XX.");
    tetromino[6].append(L".X..");
    tetromino[6].append(L".X..");

    //initialize the game field
    pField = new unsigned char[nFieldWidth*nFieldHeight];
    for (int x = 0; x < nFieldWidth; x++)
        for (int y = 0; y < nFieldHeight; y++)
            pField[y*nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;

    char *screen = new char[nScreenWidth*nScreenHeight];
    for (int i = 0; i < nScreenWidth*nScreenHeight; i++) screen[i] = L' ';
        
    //Game loop
    bool bGameOver = false;

    while (!bGameOver)
    {
        for (int x = 0; x < nFieldWidth; x++)
            for (int y = 0; y < nFieldHeight; y++)
                screen[(y + 2)*nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y*nFieldWidth + x]];

    }


    return 0;
}