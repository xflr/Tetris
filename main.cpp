#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_scancode.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include "tetris.h"

using namespace std;

bool bIsKeyPressed, bIsPKeyPressed, bIsPaused, bGameOver;
double timer = 0;
int dropSpeed = 50; // Every row completed we can decrease this value to get faster drop - 50 is 1sec and 0 is 20ms delay

SDL_Rect rect, gridRect, pauseRect;

TTF_Font* font;

SDL_Color foregroundColor = { 255, 255, 255 };
SDL_Color backgrounddColor = { 0, 0, 0 };

SDL_Window* window = NULL;
SDL_Renderer* screen = NULL;
SDL_Texture* PauseMSG;

void newBlock();

void HandleEvent(const SDL_Event& e)
{

}

shape revCols(shape s)
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

shape transposeShape(shape s)
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
            SDL_SetRenderDrawColor(screen, 50, 50, 50, 255);
            //Clear the screen. Remember, clear before draw every frame on game loop
            SDL_RenderClear(screen);
            //draw moving objects
            
            draw(cur, curGrid);
            
            if (bIsPaused){
                SDL_Surface* pauseSurface = TTF_RenderText_Solid(font, "PAUSED!", {230, 230, 230});
                PauseMSG = SDL_CreateTextureFromSurface(screen, pauseSurface);
                SDL_RenderCopy(screen, PauseMSG,  NULL,  &pauseRect);
            }

            //Render all objects (surfaces) previously added to screen
            SDL_RenderPresent(screen);
}

void rotate()
{
    cur = revCols(transposeShape(cur));
}

string willCollide(int cDirection) 
{
    switch (cDirection)
    {
    case 0:
    {    
        int gridX = cur.x;
        int gridY = cur.y;
        int tmpX;
        int tmpY;
        for (int blockX = 0; blockX < 4; blockX++)
        {
            for (int blockY = 0; blockY < 4; blockY++)
            {
                    tmpX = gridX + blockX - 1;
                    tmpY = gridY+ blockY;
                    if ( (cur.matrix[blockX][blockY]) && (curGrid.matrix[tmpY][tmpX]) )
                        { return "left_bound"; break; }
            }
        }
       
    break;
    }
    /* //OLD VERSION OF LEFT BOUNDARY COLLISION DETECTION (CASE 0). Left it here just to show how ugly the first code looks like. 
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
    */

    case 1:
    {    
        int gridX = cur.x;
        int gridY = cur.y;
        int tmpX;
        int tmpY;
        for (int blockX = 3; blockX >=  0; blockX--)
        {
            for (int blockY = 3; blockY >= 0; blockY--)
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
    {    
        int gridX = cur.x;
        int gridY = cur.y;
        int tmpX;
        int tmpY;
        for (int blockX = 3; blockX >=  0; blockX--)
        {
            for (int blockY = 3; blockY >= 0; blockY--)
            {
                    tmpX = gridX + blockX;
                    tmpY = gridY+ blockY + 1;
                    if ( (cur.matrix[blockX][blockY]) && (curGrid.matrix[tmpY][tmpX]) )
                        { newBlock(); return "bottom_b"; break; }
            }
        }
    break;
    }  

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
    //cur = blocks[4];
    cur = blocks[rand() % 7];
    rect.w=rect.h=TILE_SIZE;
    cur.x = 5; cur.y = 0;
}

void checkFullLines()
{
    //loop tru all lines and check the matrix of line y from x=1 to x=gridWidth - 1

    //if so change this whole line to 0

    //then move all lines from y=0 to y + 1 until tempY, where found the full line
}

void setRectSizes ()
{
    rect.w=rect.h=TILE_SIZE;
    cur.x = 5; cur.y = 0;

    gridRect.w=gridRect.h=TILE_SIZE;
    
    pauseRect.w = 320;
    pauseRect.h = 120;
    pauseRect.x = (SCREEN_WIDTH/2) - (pauseRect.w/2);
    pauseRect.y = (SCREEN_HEIGHT/2) - (pauseRect.h/2);
}

void update ()
{
    SDL_Event e;

    //declare state pointer to check keyboard state
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    //then loop for events and handle it. Required to monitor keyboard events, for example.
    while (SDL_PollEvent(&e) != 0)
    {       //Event handler loop. Needed to listen the keyboard inputs
        HandleEvent(e);
    }

            if( window == NULL )
            {
                printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            }
            else
            {
                if (!bIsPaused)
                {

                    //Game tick timer in 20ms (~60fps = 17ms)
                    SDL_Delay( 20 );

                    //Left and Right movement until reach the side boundaries using ternary condition for cleaner code
                    cur.x -= (state[SDL_SCANCODE_LEFT] && !(willCollide(0) == "left_bound")) ? 1 : 0;
                    cur.x += (state[SDL_SCANCODE_RIGHT] && !(willCollide(1) == "right_bound")) ? 1 : 0;
                    
                    //UP key to rotate the pieces
                    if (state[SDL_SCANCODE_UP])
                    {
                        //Check for predective collision function (willCollide) before allow the rotation.
                        if (!bIsKeyPressed && !(willCollide(2) == "top_bound") && !(willCollide(4) == "cant_rotate"))
                        {
                            rotate();
                            //Accept only one rotation cycle for each time the key is pressed. Otherwise the piece will rotate constantly and annoyingly fast 
                            bIsKeyPressed = !bIsKeyPressed ? 1 : 0;
                        }
                    } else{ bIsKeyPressed = false; } // if the current game loop found the key up released, will change the pressed state to false.

                    //Accelerate the fall of piece by pressing down key
                    cur.y += (state[SDL_SCANCODE_DOWN] && !(willCollide(3) == "bottom_b")) ? 1 : 0;
                    //Keep dropping by 1 continuously until hit the bottom boundary
                    if (timer >= dropSpeed) // the timer will respect incrementes of 50ms for every 20ms (~58fps) until drop one block position. This is = 1sec.
                    {
                        cur.y += !(willCollide(3) == "bottom_b") ? 1 : 0; //Stops the falling when hit something at the bottom. 
                        timer = 0;                                        //The collision will call another function to add the piece as part of the grid.
                    }
                }
            }

        if (state[SDL_SCANCODE_P])
        {
            if (!bIsPKeyPressed)
            {
                bIsPaused = !bIsPaused ? 1 : 0;       
                bIsPKeyPressed = true;
            }
        }
        else
        {   
            bIsPKeyPressed = false;
        }
        //Quit Screen and free memory of SDL components when press Q key            
        if (state[SDL_SCANCODE_Q])
        {   
            SDL_DestroyRenderer(screen);
            SDL_DestroyWindow(window);
            SDL_Quit();
            bGameOver = true;
            
            //return(0);
        }

    timer++;
    
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
        TTF_Init();
        font = TTF_OpenFont("Gameplay.ttf", 24);
    }
    
    if ((screen = SDL_CreateRenderer(window, -1, 0)) < 0)
    {
        printf("Error creating renderer %s\n", SDL_GetError());
    } 

    srand(time(NULL));

    bGameOver = false;
    bIsPaused = false;
    bIsPKeyPressed = false;
    bIsKeyPressed = false;

    //cur = blocks[4];
    cur = blocks[rand() % 7];
    curGrid = stage;
   
    setRectSizes();


    while (!bGameOver)
    {   

        //Update the positions after the end of 20ms game loop cycle.
        update();
        //// Things to update above, render below
        render();
        
    }
}
