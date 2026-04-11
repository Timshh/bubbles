#pragma once

#include <iostream>

#include "bubble.h"
#include "bubblefactory.h"
#include "field.h"
#include "raylib-cpp.hpp"
#include "recorder.h"

class Gamemode {
 public:
  Gamemode(int width, int height, raylib::Texture* bground,
           raylib::Texture* gameover, raylib::Texture* recordimage,
           raylib::Texture* pointsimage);
  ~Gamemode();

  Recorder* Record;
  BubbleFactory* Factory;
  Field* PlayField;
  int Width, Height;

  raylib::Texture* BgImage;
  raylib::Texture* Gameover;
  raylib::Texture* RecordImage;
  raylib::Texture* PointsImage;

  void Render();
};