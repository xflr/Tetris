#include <SDL2/SDL.h>
<<<<<<< HEAD
//#include <SDL2/SDL_keyboard.h>
=======
#include <SDL2/SDL_keyboard.h>
>>>>>>> 9961a07e8b4c937949150d6cfaa829597d497445
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
<<<<<<< HEAD
#include <vector>
#include <stdio.h>

const int TILE_SIZE = 32;

using namespace std;

bool isKeyPressed;
double timer = 0;
int dropSpeed = 50; // Every row completed we can decrease this value to get faster drop - 50 is 1sec and 0 is 20ms

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 768;

SDL_Rect rect, lBound_rect, bBound_rect, rBound_rect;
SDL_Color foregroundColor = { 255, 255, 255 };
SDL_Color backgrounddColor = { 0, 0, 0 };

SDL_Window* window = NULL;

SDL_Renderer* screen = NULL;

SDL_Texture* Message = NULL;
SDL_Texture* lBound = NULL;
SDL_Texture* bBound = NULL;
SDL_Texture* rBound = NULL;

TTF_Font* font;

struct block 
{    
    SDL_Color color;
    bool active;
};

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
        5,4,3
    },
    {
        {255,130,0},{ //I BLOCK
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}},
        5,4,4
    },
    {
        {230,255,255},{ //Z BLOCK
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}},
        5,4,3
    },
    {
        {230,50,255},{ //J BLOCK
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}},
        5,4,3
    },
    {
        {0,255,128},{ //SQUARE BLOCK
        {1,1,0,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}},
        5,4,2
    },
    {
        {0,48,128},{ //S BLOCK
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}},
        5,4,3
    },
    {
        {0,255,128},{ //T BLOCK
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}},
        5,4,3
    }
}, cur;

shape reverseCols(shape s)
{
    shape temp = s;
    for (int i = 0; i < s.size; i++)
    {
        for(int j = 0; j < s.size/2; j++)
        {
            bool t = s.matrix[i][j];
            temp.matrix[i][j]=s.matrix[i][s.size - j - 1];
            temp.matrix[i][s.size - j - 1] = t;
        }
    }
    return temp;
}
shape transpose(shape s)
{
    shape temp = s;
    for (int i = 0; i < s.size; i++)
    {
        for(int j = 0; j < s.size; j++)
        {
            temp.matrix[i][j]=s.matrix[j][i];
        }
    }
    return temp;
}

void draw(shape s)
{
    for (int i = 0; i < s.size; i++)
    {
        for(int j = 0; j < s.size; j++)
        {
            if (s.matrix[i][j])
            {
                rect.x=(s.x+i)*TILE_SIZE; rect.y=(s.y+j)*TILE_SIZE;
                SDL_SetRenderDrawColor(screen, s.color.r, s.color.g, s.color.b, 255);
                SDL_RenderFillRect(screen, &rect);
                SDL_SetRenderDrawColor(screen, 219, 219, 219, 255);
                SDL_RenderDrawRect(screen, &rect);
            }
        }
    }
}

void render()
{
    //Background color of screen
            SDL_SetRenderDrawColor(screen, 50, 0, 255, 255);
            
            //Clear the screen. Remember, clear before draw every frame on game loop
            SDL_RenderClear(screen);
            // error check while adding all components (surfaces) to screen
            
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
            //draw moving objects
            draw(cur);
            //Render all objects (surfaces) previously added to screen
            SDL_RenderPresent(screen);
            
}

void update ()
{
   timer++;
            
    //// Things to update above, render below
    render();
}
void rotate()
{
    cur = reverseCols(transpose(cur));
}

string isOnBoundaries(int cDirection) 
{
    switch (cDirection)
    {
    case 0:
        if (((cur.x * TILE_SIZE)  - TILE_SIZE)  <= 0 )
        { 
            return "left_bound";
            break;
        }
        return " ";
        break;
    case 1:
        if (((cur.x * TILE_SIZE) + cur.size * TILE_SIZE) >= (SCREEN_WIDTH - lBound_rect.w))
        { 
            return "right_bound"; 
            break;
        }
        return " ";
        break;
    
    case 2:
        if (cur.y <= 0)
        { 
            return "top_bound"; 
            break;
        }
        return " ";
        break;
    case 3:
        if ( (cur.y * TILE_SIZE)  >= ((SCREEN_HEIGHT - (bBound_rect.h ) - cur.size * TILE_SIZE) ))
        { 
            return "bottom_b"; 
            break;    
        }
        return " ";
        break;
    }
=======
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
>>>>>>> 9961a07e8b4c937949150d6cfaa829597d497445
}

void HandleEvent(const SDL_Event& e)
{

}

<<<<<<< HEAD
void setSizes()
{   
    lBound_rect.x = 0;
    lBound_rect.y = 0;
    lBound_rect.w = TILE_SIZE;
    lBound_rect.h = SCREEN_HEIGHT;

    bBound_rect.x = lBound_rect.w;
    bBound_rect.y = (SCREEN_HEIGHT - TILE_SIZE);
    bBound_rect.w = SCREEN_WIDTH - (lBound_rect.w * 2);
    bBound_rect.h = TILE_SIZE;

    rBound_rect.x = SCREEN_WIDTH - TILE_SIZE;
    rBound_rect.y = 0;
    rBound_rect.w = TILE_SIZE;
    rBound_rect.h = SCREEN_HEIGHT;
}

=======
>>>>>>> 9961a07e8b4c937949150d6cfaa829597d497445
int main ( int argc, char **argv )
{
    if (TTF_Init() < 0)
    {
        printf("ERROR TTF");
    }
    
<<<<<<< HEAD
    font = TTF_OpenFont("Courier_New.ttf", 32);
    
=======
    font = TTF_OpenFont("couri.ttf", 12);
>>>>>>> 9961a07e8b4c937949150d6cfaa829597d497445
    if (!font)
    {
        printf("ERRO FONTE %s\n", TTF_GetError());
    }
<<<<<<< HEAD
    SDL_Surface* leftBoundSurface = TTF_RenderText_Shaded(font, "#", foregroundColor, { 255, 255, 0 });
    SDL_Surface* bottomBoundSurface = TTF_RenderText_Shaded(font, "#", foregroundColor, { 255, 255, 0 });
    SDL_Surface* rightBoundSurface = TTF_RenderText_Shaded(font, "#", foregroundColor, { 255, 255, 0 });
    
=======
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "CHAMAAAAAAAAAAAAAAAAAAAAAAAA", foregroundColor);       

    
    

>>>>>>> 9961a07e8b4c937949150d6cfaa829597d497445
    if ( SDL_Init ( SDL_INIT_VIDEO ) < 0)
    {
        printf( "SDL coud not intilalize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        window = SDL_CreateWindow( "TETRIS by Alexandre Bressane - press q to quit", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0 );
    }
<<<<<<< HEAD

=======
    

    Message_rect.x = 20;
    Message_rect.y = 10;
    Message_rect.w = 800;
    Message_rect.h = 140;
>>>>>>> 9961a07e8b4c937949150d6cfaa829597d497445
    
    if ((screen = SDL_CreateRenderer(window, -1, 0)) < 0)
    {
        printf("Error creating renderer %s\n", SDL_GetError());
    } 
<<<<<<< HEAD
    srand(time(NULL));
    cur = blocks[rand() % 7];
    rect.w=rect.h=TILE_SIZE;
    cur.x = 5; cur.y = 0;
    setSizes();

    lBound = SDL_CreateTextureFromSurface(screen, leftBoundSurface);    
    bBound = SDL_CreateTextureFromSurface(screen, bottomBoundSurface);
    rBound = SDL_CreateTextureFromSurface(screen, rightBoundSurface);

    SDL_Event e;
    
    //Game loop
    bool bGameOver = false;
    isKeyPressed = false;
    while (!bGameOver)
    {   
        //declare state pointer to check keyboard state
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        //then loop for events and handle it. Required to monitor keyboard events, for example.
=======
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
>>>>>>> 9961a07e8b4c937949150d6cfaa829597d497445
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
<<<<<<< HEAD
            update();

            //Game tick timer in 17ms (~60fps)
            SDL_Delay( 20 );

            //Left and Right movement until reach the side boundaries using ternary condition for clean code
                cur.x -= (state[SDL_SCANCODE_LEFT] && !(isOnBoundaries(0) == "left_bound")) ? 1 : 0;
                cur.x += (state[SDL_SCANCODE_RIGHT] && !(isOnBoundaries(1) == "right_bound")) ? 1 : 0;
                //Just a try to hold the piece on same heigth using up key    
                if (state[SDL_SCANCODE_UP])
                {
                    if (!isKeyPressed && !(isOnBoundaries(2) == "top_bound"))
                    {
                        rotate();
                        isKeyPressed = true;
                    }
                }
                else
                {   
                    isKeyPressed = false;
                }

                //Accelerate the fall of piece by pressing down key
                cur.y += (state[SDL_SCANCODE_DOWN] && !(isOnBoundaries(3) == "bottom_b")) ? 1 : 0;
                //Keep dropping by 1 continuously until hit the bottom boundary
                if (timer >= 50)
                {
                    cur.y += !( (cur.y * TILE_SIZE)  >= ((SCREEN_HEIGHT - (bBound_rect.h ) - cur.size * TILE_SIZE) ))? 1 : 0;
                    timer = 0;
                }
            //Quit Screen freeing memory of SDL components when press Q key            
            if (state[SDL_SCANCODE_Q])
            {   
                bGameOver = true;
                SDL_FreeSurface(rightBoundSurface);
                SDL_FreeSurface(leftBoundSurface);
                SDL_FreeSurface(bottomBoundSurface);
                SDL_DestroyRenderer(screen);
                SDL_DestroyWindow(window);
                TTF_CloseFont(font);
                TTF_Quit();
                SDL_Quit();
                
                return(0);
            }
        }
=======
            
            
            
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

>>>>>>> 9961a07e8b4c937949150d6cfaa829597d497445
    }
    return 0;
}