#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

SDL_Rect Message_rect;
TTF_Font* font;

wstring tetromino[7];

int nFieldWidth = 12; //game field width
int nFieldHeight = 18; //game field height
unsigned char *pField = nullptr; //initiate field as null pointer

SDL_Color foregroundColor = { 255, 255, 255 };
SDL_Color backgrounddColor = { 0, 0, 0 };
SDL_Window* window = NULL;
SDL_Renderer* screen = NULL;
SDL_Texture* Message = NULL;

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

void HandleEvent(const SDL_Event& e)
{

}

int main ( int argc, char **argv )
{
    if (TTF_Init() < 0)
    {
        printf("ERROR TTF");
    }
    
    font = TTF_OpenFont("couri.ttf", 12);
    if (!font)
    {
        printf("ERRO FONTE %s\n", TTF_GetError());
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "CHAMAAAAAAAAAAAAAAAAAAAAAAAA", foregroundColor);       

    
    

    if ( SDL_Init ( SDL_INIT_VIDEO ) < 0)
    {
        printf( "SDL coud not intilalize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        window = SDL_CreateWindow( "TETRIS by Alexandre Bressane - press q to quit", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0 );
    }
    

    Message_rect.x = 20;
    Message_rect.y = 10;
    Message_rect.w = 800;
    Message_rect.h = 140;
    
    if ((screen = SDL_CreateRenderer(window, -1, 0)) < 0)
    {
        printf("Error creating renderer %s\n", SDL_GetError());
    } 
    Message = SDL_CreateTextureFromSurface(screen, textSurface);
    
    

    SDL_Event e;

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
 
    //Game loop
    bool bGameOver = false;
   
    while (!bGameOver)
    {
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        while (SDL_PollEvent(&e) != 0)
        {
            HandleEvent(e);
        }

        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            
            
            
            SDL_SetRenderDrawColor(screen, 50, 0, 255, 255);
            SDL_RenderClear(screen);

            if ((SDL_RenderCopy(screen, Message, NULL, &Message_rect)) < 0)
            {
                printf("ERROR RENDER COPY %s\n", SDL_GetError() );
            }
            SDL_RenderPresent(screen);

            SDL_Delay( 200 );

            Message_rect.x++;
            if (state[SDL_SCANCODE_Q])
            {
                SDL_FreeSurface(textSurface);
                TTF_CloseFont(font);
                TTF_Quit();
                SDL_Quit();
                bGameOver = true;
                return(0);
            } 
        }

    }
    return 0;
}