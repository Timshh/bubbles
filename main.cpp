#include <ctime>

#include "bubblefactory.h"
#include "field.h"
#include "gamemode.h"
#include "raylib-cpp.hpp"
#include "recorder.h"

using namespace std;

int main() {
  srand(time(NULL));
  int screenWidth = 1000;
  int screenHeight = 700;
  raylib::Window window(screenWidth, screenHeight, "Bubbles");
  raylib::Texture bgimage("res/bgimage.png");
  raylib::Texture gameover("res/gameover.png");
  raylib::Texture recordimage("res/record.png");
  raylib::Texture pointsimage("res/points.png");
  SetTargetFPS(60);
  Gamemode gamemode(9, 9, &bgimage, &gameover, &recordimage, &pointsimage);

  raylib::Color background = BLACK;

  while (!window.ShouldClose()) {
    BeginDrawing();
    window.ClearBackground(background);

    gamemode.Render();

    EndDrawing();
  }
  gamemode.Record->UpdateStatistic();
  CloseAudioDevice();
  return 0;
}
