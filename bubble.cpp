#include "raylib-cpp.hpp"
#include "bubble.h"

Bubble::Bubble(raylib::Color bubblecolor) {
  X = 0;
  Y = 0;
  BubbleColor = bubblecolor;
}

void Bubble::SetCoord(int newX, int newY) {
  X = newX;
  Y = newY;
}

void Bubble::SetSelection(bool state) { IsSelected = state; }

void Bubble::Render() { DrawCircle(X, Y, Radius, BubbleColor);
  DrawCircle(X, Y, Radius, BubbleColor);
  DrawCircleLines(X, Y, Radius, Outline);
  if (IsSelected) {
    DrawCircle(X, Y, Radius/2, BLACK);
  }
}

Bubble::~Bubble() {}