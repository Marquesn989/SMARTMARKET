#include "raylib.h"
#include <string>

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "SmartMarket - C++ Raylib Test");
    SetTargetFPS(60);

    Color brandBlue = { 10, 36, 99, 255 };
    std::string msg = "Hello from C++ + raylib!";

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(0, 0, screenWidth, 64, brandBlue);
        DrawText("SmartMarket (C++)", 16, 20, 24, RAYWHITE);

        DrawText(msg.c_str(), 120, 200, 24, DARKBLUE);
        DrawText("ESC to quit", 16, screenHeight - 28, 18, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}