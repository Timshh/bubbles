#pragma once

#include <iostream>
#include "raylib-cpp.hpp"

enum BubbleState { 
	Growing,
	Idle,
	Selected,
	Moving,
	Destroying,
	Terminated
};

class Bubble {
 public:
  raylib::Color BubbleColor;
  int X, Y, NewX = 0, NewY = 0;
  float Radius = 30.0f, Mult = 1.0f;
  BubbleState State = Growing;
  Bubble(raylib::Color bubblecolor);
  ~Bubble();
  void Tick();
  void Destruct();
  void MoveTo(int newX, int newY);
  void SetSelection(bool state);

 private:
  const raylib::Color Outline = raylib::Color(0, 0, 0, 120);
  const int BaseRadius = 30;
};