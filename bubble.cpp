#include "raylib-cpp.hpp"
#include "bubble.h"

Bubble::Bubble(raylib::Color bubblecolor) {
  X = -100;
  Y = -100;
  BubbleColor = bubblecolor;
}

void Bubble::Destruct() { IsDestructed = true; }

void Bubble::ChangeCoord(int newX, int newY) {
  NewX = newX;
  NewY = newY;
  IsMoving = true;
  MoveTime = 0;
}

void Bubble::SetSelection(bool state) {
  if (!IsDestructed) {
    IsSelected = state;
    if (!IsSelected) {
      Radius = BaseRadius;
      Tick = 0;
      Mult = 1;
    }
  }
}

bool Bubble::Render() { DrawCircle(X, Y, Radius, BubbleColor);
  if (IsDestructed) {
    Delay++;
    Radius = BaseRadius - Delay;
    if (Delay == 30) {
      return true;
    }
  }
  if (IsMoving) {
    MoveTime++;
    Radius = abs(BaseRadius - MoveTime*2);
    if (MoveTime == 15) {
      X = NewX;
      Y = NewY;
    }
    if (MoveTime == 30) {
      IsMoving = false;
    }
  }
  if (IsSelected) {
    if (Tick == 0) {
      Radius -= 2 * Mult;
      if (Radius == BaseRadius - 4) {
        Mult = -1;
      } 
      if (Radius == BaseRadius) {
        Mult = 1;
      } 
    }
    DrawCircle(X, Y, Radius, BubbleColor);
    DrawCircleLines(X, Y, Radius, Outline);
    DrawCircle(X, Y, Radius/2, BLACK);
    Tick = (Tick + 1) % 30;
  } else {
    DrawCircle(X, Y, Radius, BubbleColor);
    DrawCircleLines(X, Y, Radius, Outline);
  }
  return false;
}

Bubble::~Bubble() {}