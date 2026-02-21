#pragma once

#include <iostream>
#include <fstream>
#include "raylib-cpp.hpp"
#include "bubble.h"
#include "bubblefactory.h"

class Field {
public:
  Field(int width, int height, BubbleFactory* factory);
    ~Field();
        BubbleFactory* Factory;
    int Width, Height, CellSize, OffsetX, OffsetY, HighlightedCelX,
        HighlightedCelY, SelectedX = 0, SelectedY = 0, Points = 0,
                         Record = 0, MoveDelay = 0, DestroyDelay = 0;
    Vector2 CurrentCoords[3];
    Bubble *Bubble1, *Bubble2, *Bubble3;
    std::fstream* File;
    bool IsPressed = false, CanAct = true, CanThrow = true, IsDelay = false, ThrowAfterDelay = false, IsOver = false, IsMoving = false, IsClicked = false;
    void Render();
    void PathCleaner();
    bool PathFinder(int startX, int startY, int endX, int endY);
    void Click();
    void ProcessInput();
    void BubblesCreate();
    void BubblesThrow();
    void Restart();
    void TickTimer();
    bool Research(int X, int Y);
    bool Search(int X, int Y, int XChange, int YChange, raylib::Color Target);
    void Destroy(int X, int Y, int XChange, int YChange, int ForawrdLength,
                 int BackwardLength);


protected:
    const raylib::Color CellColor = RAYWHITE;
    const raylib::Color TextColor = WHITE;
    const raylib::Color HighlightedColor = raylib::Color(125, 125, 125, 200);
    std::vector<std::vector<Bubble*>> Bubbles;
    std::vector<std::vector<int>> Paths;

};