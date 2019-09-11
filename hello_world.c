#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Hello World");

    SetTargetFPS(60);               
     while (!WindowShouldClose()) 
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Hello World!", 10, 10, 20, LIME);

        EndDrawing();
        
    }

   
    CloseWindow();
   

    return 0;
}