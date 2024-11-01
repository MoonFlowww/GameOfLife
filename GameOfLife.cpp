
#define WIN32_LEAN_AND_MEAN  // Exclure les APIs non n�cessaires
#define NOGDI                // Exclure Graphics Device Interface
#define NOMINMAX             // D�sactive min et max de Windows
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

    /* Sparcler
    logic.GridSetCell(5, 6, 1);
    logic.GridSetCell(6, 6, 1);
    logic.GridSetCell(7, 6, 1);
    */
    

    
    /*
    
    */
        
    


    while (!WindowShouldClose()) {
        logic.HandleMouseInput();
        logic.Update();

        BeginDrawing();
        ClearBackground(GREY);
        logic.GridDraw();
        EndDrawing();
    }

    CloseWindow();
}
