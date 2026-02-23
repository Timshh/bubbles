#pragma once

#include <iostream>
#include "raylib-cpp.hpp"
#include "bubble.h"
#include "bubblefactory.h"
#include "recorder.h"

//enum FieldState { Idle, Moving, Spawning, Destroying, GameOver };

class Field {
public:
  Field(int width, int height, BubbleFactory* factory, Recorder* recorder);
  ~Field();
  Recorder* Record;
  BubbleFactory* Factory;
  int Width, Height, CellSize, OffsetX, OffsetY, HighlightedCelX,
      HighlightedCelY, SelectedX = 0, SelectedY = 0, MoveDelay = 0,
                       DestroyDelay = 0;
    Vector2 CurrentCoords[3];
    Bubble *Bubble1, *Bubble2, *Bubble3;
    //FieldState State = Idle;
    bool IsPressed = false, CanAct = true, CanThrow = true, IsDelay = false, ThrowAfterDelay = false, IsOver = false, IsMoving = false, IsClicked = false;
    
    void Render();
    void TickTimer();
    
    void PathCleaner();
    bool PathFinder(int startX, int startY, int endX, int endY);

    void Click();
    void ProcessInput();
    
    void Restart();
    void BubblesCreate();
    void BubblesThrow();
   
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