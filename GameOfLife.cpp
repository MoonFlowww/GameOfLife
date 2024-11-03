
// errors between Matplot++ and Raylib
#define WIN32_LEAN_AND_MEAN  // Exclure les APIs non nécessaires
#define NOGDI                // Exclure Graphics Device Interface
#define NOMINMAX             // Désactive min et max de Windows
#define NOUSER               // Exclure USER APIs (ShowCursor, etc.)
#define NOSOUND              // Exclure APIs pour le son

#include <Windows.h>
#include <raylib.h>

#include <iostream>
#include "logic.h"
int main()
{
    Color GREY = { 25, 25, 25, 255 };
    const int Window_Width = 1000;
    const int Window_Height = 1000;
    const int Cell_Size = 15;
    const int FPS = 240;
    InitWindow(Window_Width, Window_Height, "Game of Life");
    SetTargetFPS(FPS);
    LOGIC logic(Window_Width, Window_Height, Cell_Size);

    while (!WindowShouldClose()) {
        logic.HandleMouseInput();
        logic.Update(); // add true for chart

        BeginDrawing();
        ClearBackground(GREY);
        logic.GridDraw();
        EndDrawing();
    }

    CloseWindow();
}
