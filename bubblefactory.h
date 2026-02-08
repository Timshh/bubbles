#pragma once

#include <iostream>
#include "bubble.h"
#include "raylib-cpp.hpp"

class BubbleFactory {
 public:
  raylib::Color Colors[5] = {YELLOW, RAYWHITE, SKYBLUE, GREEN, RED};
  Bubble* CreateBubble();
};