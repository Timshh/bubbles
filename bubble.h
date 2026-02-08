#pragma once

#include <iostream>
#include "raylib-cpp.hpp"

class Bubble {
 public:
  Bubble(raylib::Color bubblecolor);	
  ~Bubble();
  raylib::Color BubbleColor, Outline = raylib::Color(0, 0, 0, 120);
  int X, Y;
  const int Radius = 30;
  bool IsSelected = false;
  void Render();
  void SetCoord(int newX, int newY);
  void SetSelection(bool state);
};