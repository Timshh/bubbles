#pragma once

#include <iostream>
#include "raylib-cpp.hpp"

class Bubble {
 public:
  Bubble(raylib::Color bubblecolor);	
  void Destruct();
  ~Bubble();
  raylib::Color BubbleColor, Outline = raylib::Color(0, 0, 0, 120);
  int X, Y, NewX, NewY, Delay = 0, MoveTime = 0, Tick = 0, Radius = 30, Mult = 1; 
  const int BaseRadius = 30;
  bool IsSelected = false, IsMoving = false, IsDestructed = false;
  bool Render();
  void ChangeCoord(int newX, int newY);
  void SetSelection(bool state);
};