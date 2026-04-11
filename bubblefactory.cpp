#include "bubblefactory.h"

#include "bubble.h"
#include "field.h"
#include "raylib-cpp.hpp"

Bubble* BubbleFactory::CreateBubble() { return new Bubble(Colors[rand() % 5]); }
