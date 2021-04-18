#include <SDL2/SDL.h>
#include <SDL2/SDL_scancode.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include "tetris.h"

const int TILE_SIZE = 32;

using namespace std;

bool isKeyPressed;
double timer = 0;
int dropSpeed = 50; // Every row completed we can decrease this value to get faster drop - 50 is 1sec and 0 is 20ms

SDL_Rect rect, gridRect;
SDL_Color foregroundColor = { 255, 255, 255 };
SDL_Color backgrounddColor = { 0, 0, 0 };

SDL_Window* window = NULL;

SDL_Renderer* screen = NULL;

SDL_Texture* Message = NULL;
SDL_Texture* lBound = NULL;
SDL_Texture* bBound = NULL;
SDL_Texture* rBound = NULL;

void newBlock();

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

void draw(shape s, grid g)
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
    double screenDrawX, screenDrawY;
    //draw stage
    for (int i = 0; i < gridWidth; i++)
    {
        for(int j = 0; j < gridHeight; j++)
        {
            if (curGrid.matrix[j][i])
            {
                screenDrawX = (i * TILE_SIZE) ;
                screenDrawY = (j * TILE_SIZE) ;
                gridRect.x=screenDrawX; gridRect.y=screenDrawY;

                SDL_SetRenderDrawColor(screen, 255, 255, 255, 255);
                SDL_RenderFillRect(screen, &gridRect);
                SDL_SetRenderDrawColor(screen, 219, 219, 219, 255);
                SDL_RenderDrawRect(screen, &gridRect);
            }
        }
    }
}

void render()
{
            //Background color of screen
            SDL_SetRenderDrawColor(screen, 50, 0, 155, 255);
            //Clear the screen. Remember, clear before draw every frame on game loop
            SDL_RenderClear(screen);
            //draw moving objects
            draw(cur, curGrid);
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

        if (cur.x == 1) {
            if ( (cur.matrix[0][0]) || (cur.matrix[0][1]) || (cur.matrix[0][2]) || (cur.matrix[0][3]) ) {
                return "left_bound";
                break;
            }
        }
        if (cur.x == 0) {
            if ( (cur.matrix[1][0]) || (cur.matrix[1][1]) || (cur.matrix[1][2]) || (cur.matrix[1][3]) ) {
                return "left_bound";
                break;
            }
        }
        if (cur.x == -1) {
            if ( (cur.matrix[2][0]) || (cur.matrix[2][1]) || (cur.matrix[2][2]) || (cur.matrix[2][3]) ) {
                return "left_bound";
                break;
            }
        }
        if (cur.x == -2) {
            if ( (cur.matrix[3][0]) || (cur.matrix[3][1]) || (cur.matrix[3][2]) || (cur.matrix[3][3]) ) {
                return "left_bound";
                break;
            }
        }
        else
        {
            return " ";
            break;
        }
    return " ";
    break; 

    case 1:
    {    
        int gridX = cur.x;
        int gridY = cur.y;
        int tmpX;
        int tmpY;
        for (int blockX = 4; blockX >=  0; blockX--)
        {
            for (int blockY = 4; blockY >= 0; blockY--)
            {
                    tmpX = gridX + blockX + 1;
                    tmpY = gridY+ blockY;
                    if ( (cur.matrix[blockX][blockY]) && (curGrid.matrix[tmpY][tmpX]) )
                        { return "right_bound"; break; }

            }
        }
       
    break;
    }  
    case 2:
        if (cur.y <= 0)
            return "top_bound"; 
            break;
        
        return " ";
        break;

    case 3:
        if ( (cur.y * TILE_SIZE)  >= ((SCREEN_HEIGHT - 1 - cur.size * TILE_SIZE) ))
        {
            if ((cur.matrix[0][4]) || (cur.matrix[1][4]) || (cur.matrix[2][4]) || (cur.matrix[3][4]))
            {
                newBlock();
                return "bottom_b"; 
                break;
                
            }
            else
            {   
                return " ";
                break;
            
            }
            return " ";    
            break;    
        }
        return " ";
        break;
    case 4:
        //Chek if rotation is possible when on left boundary
        if ( (cur.x == 1)){
            if (cur.size == 3){
                if ((cur.matrix[1][2] == true) || (cur.matrix[2][2] == true))
                    return "cant_rotate"; 
                    break;  
            }
            if (cur.size == 4) {
                if ((cur.matrix[1][3] == true) || (cur.matrix[2][3] == true) || (cur.matrix[3][3] == true ) && cur.matrix[3][2])
                    return "cant_rotate"; 
                    break;    
            }
        }
        if ( (cur.x <= 0) ){
            if (cur.size == 3){
                if ((cur.matrix[1][2] == true) || (cur.matrix[2][2] == true))
                    return "cant_rotate"; 
                    break;  
            }
            if (cur.size == 4) {
                if ((cur.matrix[1][3] == true) || (cur.matrix[2][3] == true) || (cur.matrix[3][3] == true ) && cur.matrix[3][2])
                    return "cant_rotate"; 
                    break;    
            }
        }
        
        //Chek if rotation is possible when on right boundary
        if ( ((cur.x + cur.size)) == (gridWidth - 2)) {
            if (cur.size == 3){
                if ((cur.matrix[1][2] == true) || (cur.matrix[2][2] == true))
                    return "cant_rotate"; 
                    break;  
            }
            if (cur.size == 4) {
                if ((cur.matrix[1][3] == true) || (cur.matrix[2][3] == true) || (cur.matrix[3][3] == true ) && cur.matrix[3][2])
                    return "cant_rotate"; 
                    break;    
            }
        }
        if ( ((cur.x + cur.size) - 1) >= (gridWidth - 2)) {
            if (cur.size == 3){
                if ((cur.matrix[1][2] == true) || (cur.matrix[2][2] == true))
                    return "cant_rotate"; 
                    break;  
            }
            if (cur.size == 4) {
                if ((cur.matrix[1][3] == true) || (cur.matrix[2][3] == true) || (cur.matrix[3][3] == true ) && cur.matrix[3][2])
                    return "cant_rotate"; 
                    break;    
            }
        }
        return " ";
        break;
    }
    return " ";
}

void newBlock() 
{
    int matX, matY;
    //shape stage[cur.x][cur.y] += cur;
    for (int i = 0; i < cur.size; i++)
    {
        for(int j = 0; j < cur.size; j++)
        {
            if (cur.matrix[i][j])
            {
                matX = cur.x + i;
                matY = cur.y + j;
                curGrid.matrix[matY][matX] = cur.matrix[i][j];
            }
        }
    }

    cur = blocks[rand() % 7];
    rect.w=rect.h=TILE_SIZE;
    cur.x = 5; cur.y = 0;
    
}
void HandleEvent(const SDL_Event& e)
{

}



int main ( int argc, char **argv )
{
    
    if ( SDL_Init ( SDL_INIT_VIDEO ) < 0)
    {
        printf( "SDL coud not intilalize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        window = SDL_CreateWindow( "TETRIS by Alexandre Bressane - press q to quit", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0 );
    }
    
    if ((screen = SDL_CreateRenderer(window, -1, 0)) < 0)
    {
        printf("Error creating renderer %s\n", SDL_GetError());
    } 
    srand(time(NULL));
    cur = blocks[4];
    //cur = blocks[rand() % 7];
    rect.w=rect.h=TILE_SIZE;
    cur.x = 5; cur.y = 0;

    gridRect.w=gridRect.h=TILE_SIZE;
    
    curGrid = stage;
   
    SDL_Event e;
    
    //Game loop
    bool bGameOver = false;
    isKeyPressed = false;
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
            update();

            //Game tick timer in 17ms (~60fps)
            SDL_Delay( 20 );

            //Left and Right movement until reach the side boundaries using ternary condition for clean code
                cur.x -= (state[SDL_SCANCODE_LEFT] && !(isOnBoundaries(0) == "left_bound")) ? 1 : 0;
                cur.x += (state[SDL_SCANCODE_RIGHT] && !(isOnBoundaries(1) == "right_bound")) ? 1 : 0;
                //Just a try to hold the piece on same heigth using up key    
                if (state[SDL_SCANCODE_UP])
                {
                    if (!isKeyPressed && !(isOnBoundaries(2) == "top_bound") && !(isOnBoundaries(4) == "cant_rotate"))
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
                if (timer >= dropSpeed)
                {
                    cur.y += !(((cur.y * TILE_SIZE)  >= SCREEN_HEIGHT) && !(isOnBoundaries(3) == "bottom_b")) ? 1 : 0;
                    timer = 0;
                }
            //Quit Screen freeing memory of SDL components when press Q key            
            if (state[SDL_SCANCODE_Q])
            {   
                bGameOver = true;
                SDL_DestroyRenderer(screen);
                SDL_DestroyWindow(window);
                SDL_Quit();
                
                return(0);
            }
        }
    }
    return 0;
}