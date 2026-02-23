#include "raylib-cpp.hpp"
#include "bubble.h"

Bubble::Bubble(raylib::Color bubblecolor) {
  X = -100;
  Y = -100;
  BubbleColor = bubblecolor;
}

void Bubble::Destruct() {
  State = Destroying;
  Mult = -1;
}

void Bubble::MoveTo(int newX, int newY) {
  NewX = newX;
  NewY = newY;
  State = Moving;
  Mult = -1;
}

void Bubble::SetSelection(bool newSelected) {
  if (newSelected) {
    if (State != Selected) {
      State = Selected;
      Mult = -1;
    }
  }else {
    State = Idle;
    Radius = BaseRadius;
    Mult = -1;
  }
}

void Bubble::Tick() {
  Radius += Mult;
  switch (State) {
    case Growing:
      if (Radius == BaseRadius) {
        Mult = 0;
        State = Idle;
      }
      break;
    case Idle:
      if (Radius <= BaseRadius) {
        Mult = 1;
      } else {
        Mult = 0;
      }
      break;
    case Selected:
      if (Radius <= BaseRadius - 10) {
        Mult = 0.2;
      }
      if (Radius >= BaseRadius) {
        Mult = -0.2;
      }
      break;
    case Moving:
      if (Radius <= 0) {
        X = NewX;
        Y = NewY;
        Mult = 1;
      }
      if (Radius >= BaseRadius and Mult == 1) {
        State = Idle;
        Mult = 0;
      }
      break;
    case Destroying:
      if (Radius <= 0) {
        State = Terminated;
        Radius = 0;
        Mult = 0;
      }
      break;
  }
  DrawCircle(X, Y, Radius, BubbleColor);
  DrawCircleLines(X, Y, Radius, Outline);
}

Bubble::~Bubble() {}