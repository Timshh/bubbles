#include "raylib-cpp.hpp"
#include "main.h"
#include "field.h"
#include "bubblefactory.h"
#include<ctime>

using namespace std;



int main() {
    srand(time(NULL));
    int screenWidth = 1000;
    int screenHeight = 700;
    SetTargetFPS(60);
    BubbleFactory Factory;
    Field field(9, 9, &Factory);
    field.BubblesCreate();
    field.BubblesThrow();

    raylib::Window window(screenWidth, screenHeight, "Bubbles");
    raylib::Texture bgimage("res/bgimage.png");
    raylib::Texture gameover("res/gameover.png");
    raylib::Color color1(0, 68, 130);
    raylib::Color color2(100, 68, 10);
    raylib::Color background = BLACK;

    while (!window.ShouldClose())
    {

        BeginDrawing();
        window.ClearBackground(background);

        bgimage.Draw(screenWidth - bgimage.GetWidth(),
                     screenHeight - bgimage.GetHeight());

        field.ProcessInput();
        field.Render();

        if (!field.CanAct) {
          gameover.Draw(-270,-100);
        }

        EndDrawing();
        
    }

    return 0;
}

