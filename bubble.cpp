#include "bubble.h"

#include "raylib-cpp.hpp"

Bubble::Bubble(raylib::Color bubblecolor) {
  X = -100;
  Y = -100;
  BubbleColor = bubblecolor;
}

void Bubble::Destruct() {
  State = BubbleState::Destroying;
  Mult = -1;
}

void Bubble::MoveTo(int newX, int newY) {
  NewX = newX;
  NewY = newY;
  State = BubbleState::Moving;
  Mult = -1;
}

void Bubble::SetSelection(bool newSelected) {
  if (newSelected) {
    if (State != BubbleState::Selected) {
      State = BubbleState::Selected;
    }
  } else {
    State = BubbleState::Idle;
  }
}

void Bubble::Tick() {
  Radius += Mult;
  switch (State) {
    case BubbleState::Growing:
      if (Radius >= BaseRadius) {
        Mult = 0;
        Radius = BaseRadius;
        State = BubbleState::Idle;
      }
      break;
    case BubbleState::Idle:
      if (Radius <= BaseRadius) {
        Mult = 0.4;
      } else {
        Mult = 0;
      }
      break;
    case BubbleState::Selected:
      if (Radius <= BaseRadius - 10) {
        Mult = 0.2;
      }
      if (Radius >= BaseRadius) {
        Mult = -0.2;
      }
      break;
    case BubbleState::Moving:
      if (Radius <= 0) {
        X = NewX;
        Y = NewY;
        Mult = 1;
      }
      if (Radius >= BaseRadius and Mult == 1) {
        State = BubbleState::Idle;
        Mult = 0;
      }
      break;
    case BubbleState::Destroying:
      if (Radius <= 0) {
        State = BubbleState::Terminated;
        Radius = 0;
        Mult = 0;
      }
      break;
  }
  DrawCircle(X, Y, Radius, BubbleColor);
  DrawCircleLines(X, Y, Radius, Outline);
}

Bubble::~Bubble() {}