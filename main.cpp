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

SDL_Rect Message_rect, lBound_rect, bBound_rect, rBound_rect;
SDL_Color foregroundColor = { 255, 255, 255 };
SDL_Color backgrounddColor = { 0, 0, 0 };

SDL_Window* window = NULL;

SDL_Renderer* screen = NULL;

SDL_Texture* Message = NULL;
SDL_Texture* lBound = NULL;
SDL_Texture* bBound = NULL;
SDL_Texture* rBound = NULL;

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
        if ( Message_rect.x <= lBound_rect.w )
        { 
            return "left_bound";
            break;
        }
        return " ";
        break;
    case 1:
        if ( (Message_rect.x + Message_rect.w) >= (SCREEN_WIDTH - rBound_rect.w))
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
        if ( (Message_rect.y + Message_rect.h) >= (SCREEN_HEIGHT - bBound_rect.h))
        { 
            return "bottom_b"; 
            break;    
        }
        return " ";
        break;
    }
}

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

void setSizes()
{
    Message_rect.x = 20;
    Message_rect.y = 10;
    Message_rect.w = 480;
    Message_rect.h = 240;
    
    lBound_rect.x = 0;
    lBound_rect.y = 0;
    lBound_rect.w = 15;
    lBound_rect.h = SCREEN_HEIGHT;

    bBound_rect.x = lBound_rect.w;
    bBound_rect.y = (SCREEN_HEIGHT - 15);
    bBound_rect.w = SCREEN_WIDTH - (lBound_rect.w * 2);
    bBound_rect.h = 15;

    rBound_rect.x = SCREEN_WIDTH - 15;
    rBound_rect.y = 0;
    rBound_rect.w = 15;
    rBound_rect.h = SCREEN_HEIGHT;

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
    SDL_Surface* leftBoundSurface = TTF_RenderText_Shaded(font, " ", foregroundColor, { 255, 255, 0 });
    SDL_Surface* bottomBoundSurface = TTF_RenderText_Shaded(font, " ", foregroundColor, { 255, 255, 0 });
    SDL_Surface* rightBoundSurface = TTF_RenderText_Shaded(font, " ", foregroundColor, { 255, 255, 0 });
    
    
    if ( SDL_Init ( SDL_INIT_VIDEO ) < 0)
    {
        printf( "SDL coud not intilalize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        window = SDL_CreateWindow( "TETRIS by Alexandre Bressane - press q to quit", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0 );
    }

    setSizes();

    if ((screen = SDL_CreateRenderer(window, -1, 0)) < 0)
    {
        printf("Error creating renderer %s\n", SDL_GetError());
    } 
    
    Message = SDL_CreateTextureFromSurface(screen, textSurface);
    lBound = SDL_CreateTextureFromSurface(screen, leftBoundSurface);    
    bBound = SDL_CreateTextureFromSurface(screen, bottomBoundSurface);
    rBound = SDL_CreateTextureFromSurface(screen, rightBoundSurface);

    SDL_Event e;

    
    //Game loop
    bool bGameOver = false;
   
    while (!bGameOver)
    {   
        //declare state pointer to check keyboard state
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        //then loop for events and handle it. Required to monitor keyboard events, for example.
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
            //Background color of screen
            SDL_SetRenderDrawColor(screen, 50, 0, 255, 255);
            //Clear the screen. Remember, clear before draw every frame on game loop
            SDL_RenderClear(screen);
            // error check while adding all components (surfaces) to screen
            if ((SDL_RenderCopy(screen, Message, NULL, &Message_rect)) < 0)
            {
                printf("ERROR RENDER COPY %s\n", SDL_GetError() );
            }
            if ((SDL_RenderCopy(screen, lBound, NULL, &lBound_rect)) < 0)
            {
                printf("ERROR RENDER COPY %s\n", SDL_GetError() );
            }
            if ((SDL_RenderCopy(screen, bBound, NULL, &bBound_rect)) < 0)
            {
                printf("ERROR RENDER COPY %s\n", SDL_GetError() );
            }
            if ((SDL_RenderCopy(screen, rBound, NULL, &rBound_rect)) < 0)
            {
                printf("ERROR RENDER COPY %s\n", SDL_GetError() );
            }

            //Render all objects (surfaces) previously added to screen
            SDL_RenderPresent(screen);

            //Game tick timer in 17ms (~60fps)
            SDL_Delay( 17 );

            //Quit Screen freeing memory of SDL components when press Q key            
            if (state[SDL_SCANCODE_Q])
            {
                SDL_FreeSurface(textSurface);
                SDL_FreeSurface(rightBoundSurface);
                SDL_FreeSurface(leftBoundSurface);
                SDL_FreeSurface(bottomBoundSurface);
                TTF_CloseFont(font);
                TTF_Quit();
                SDL_Quit();
                bGameOver = true;
                return(0);
            }
            //Left and Right movement until reach the side boundaries using ternary condition for clean code
            Message_rect.x -= (state[SDL_SCANCODE_LEFT] && !(isOnBoundaries(0) == "left_bound")) ? 5 : 0;
            Message_rect.x += (state[SDL_SCANCODE_RIGHT] && !(isOnBoundaries(1) == "right_bound")) ? 5 : 0;
            //Just a try to hold the piece on same heigth using up key    
            Message_rect.y -= (state[SDL_SCANCODE_UP] && !(isOnBoundaries(2) == "top_bound")) ? 1 : 0;
            //Accelerate the fall of piece by pressing down key
            Message_rect.y += (state[SDL_SCANCODE_DOWN] && !(isOnBoundaries(3) == "bottom_b")) ? 5 : 0;
            //Keep dropping by 1 continuously until hit the bottom boundary
            Message_rect.y += !((Message_rect.y + Message_rect.h) >= (SCREEN_HEIGHT - bBound_rect.h)) ? 1 : 0;
        }
    }
    return 0;
}