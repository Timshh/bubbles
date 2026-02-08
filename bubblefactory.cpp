#include "raylib-cpp.hpp"
#include "field.h"
#include "bubble.h"
#include "bubblefactory.h"

Bubble* BubbleFactory::CreateBubble() { 
	return new Bubble(Colors[rand()%5]);
}
