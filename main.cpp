#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
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

string isOnBoundaries(int cDirection) 
{
    switch (cDirection)
    {
    case 0:
        if ( Message_rect.x <= 0 )
        { 
            return "left_bound"; 
            break;
        }
        return " ";
        break;
    case 1:
        if ( (Message_rect.x + Message_rect.w) >= SCREEN_WIDTH)
        { 
            return "right_bound"; 
            break;
        }
        return " ";
        break;
    
    case 2:
        if (Message_rect.y <= 0)
        { 
            return "top_bound"; 
            break;
        }
        return " ";
        break;
    case 3:
        if ( (Message_rect.y + Message_rect.h) >= SCREEN_HEIGHT)
        { 
            return "bottom_b"; 
            break;    
        }
        return " ";
        break;
    }
}

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
    
    font = TTF_OpenFont("Courier_New.ttf", 32);
    
    if (!font)
    {
        printf("ERRO FONTE %s\n", TTF_GetError());
    }
    SDL_Surface* textSurface = TTF_RenderText_Shaded(font, "CHAMA!", foregroundColor, { 255, 50, 0 });       
    SDL_Surface* leftBoundSurface = TTF_RenderText_Shaded(font, "#", foregroundColor, { 255, 255, 0 });
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
    Message_rect.w = 480;
    Message_rect.h = 240;
    
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

            SDL_Delay( 17 );

            
            if (state[SDL_SCANCODE_Q])
            {
                SDL_FreeSurface(textSurface);
                TTF_CloseFont(font);
                TTF_Quit();
                SDL_Quit();
                bGameOver = true;
                return(0);
            }

            if (state[SDL_SCANCODE_LEFT])
            {
                // keep it here to know we can change the text/texture in the gameloop
                //SDL_Surface* textSurface = TTF_RenderText_Solid(font, "PAHHHH", foregroundColor);
                //Message = SDL_CreateTextureFromSurface(screen, textSurface);
                if (!(isOnBoundaries(0) == "left_bound"))
                {
                    Message_rect.x--;
                }
            } 
            if (state[SDL_SCANCODE_RIGHT])
            {
                // keep it here to know we can change the text/texture in the gameloop
                //SDL_Surface* textSurface = TTF_RenderText_Solid(font, "PAHHHH", foregroundColor);
                //Message = SDL_CreateTextureFromSurface(screen, textSurface);
                if (!(isOnBoundaries(1) == "right_bound"))
                {
                    Message_rect.x++;
                }
            } 
            if (state[SDL_SCANCODE_UP])
            {
                // keep it here to know we can change the text/texture in the gameloop
                //SDL_Surface* textSurface = TTF_RenderText_Solid(font, "PAHHHH", foregroundColor);
                //Message = SDL_CreateTextureFromSurface(screen, textSurface);
                if (!(isOnBoundaries(2) == "top_bound"))
                {
                    Message_rect.y--;
                }
            }
            if (state[SDL_SCANCODE_DOWN])
            {
                // keep it here to know we can change the text/texture in the gameloop
                //SDL_Surface* textSurface = TTF_RenderText_Solid(font, "PAHHHH", foregroundColor);
                //Message = SDL_CreateTextureFromSurface(screen, textSurface);
                if (!(isOnBoundaries(3) == "bottom_b"))
                {    
                    Message_rect.y++;
                }
            } 
        }

    }
    return 0;
}