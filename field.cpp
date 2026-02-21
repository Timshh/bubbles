#include "field.h"

Field::Field(int width, int height, BubbleFactory* factory)
    : Bubbles(height, std::vector<Bubble*>(width)), Paths(height, std::vector<int>(width)) {
  Width = width;
  Height = height;
  CellSize = 70;
  OffsetX = 130;
  OffsetY = 35;
  Factory = factory;
  std::fstream File("record.txt", std::ios::in);
  if (File >> Record) {
  } else {
    Record = 0;
  }
  File.close();
  for (int x = 0; x < Width; x++) {
    for (int y = 0; y < Height; y++) {
      Bubbles[x][y] = nullptr;
    }
  }
}

Field::~Field() {}

void Field::Render() {
  TickTimer();
  DrawRectangle(OffsetX, OffsetY, CellSize * Width, CellSize * Height, raylib::Color(0,0,0,50));
  for (int x = 0; x < Width; x++) {
    for (int y = 0; y < Height; y++) {
      DrawRectangleLines(OffsetX + x * CellSize, OffsetY + y * CellSize,
                         CellSize, CellSize, CellColor);
    }
  }
  if (HighlightedCelX >= 0 and HighlightedCelX < Width and HighlightedCelY >=0 and HighlightedCelY < Height) {
    DrawRectangle(OffsetX + HighlightedCelX * CellSize,
                  OffsetY + HighlightedCelY * CellSize, CellSize - 1, CellSize - 1,
                  HighlightedColor);
  }
  for (int i = 0; i < 3; i++) {
    DrawRectangleLines(OffsetX + 700, OffsetY + 200 + i*CellSize, CellSize, CellSize, CellColor);
  }
  for (int x = 0; x < Width; x++) {
    for (int y = 0; y < Height; y++) {
      if (Bubbles[x][y]) {
        if (Bubbles[x][y]->Render()) {
          delete Bubbles[x][y];
          Bubbles[x][y] = nullptr;
        }
      }
    }
  }
  DrawText(std::to_string(Points), OffsetX + 690, OffsetY + 45, 30, TextColor);
  DrawText(std::to_string(Record), OffsetX + 690, OffsetY + 490, 30, TextColor);
  if (Bubble1) {
    Bubble1->Render();
    Bubble2->Render();
    Bubble3->Render();
  }
  if (IsPressed != IsMouseButtonDown(0) and IsPressed == false) {
    Click();
  }
  IsPressed = IsMouseButtonDown(0);
  
}

void Field::PathCleaner() {
  for (int x = 0; x < Width; x++) {
    for (int y = 0; y < Height; y++) {
      if (!Bubbles[x][y]) {
        Paths[x][y] = 0;
      } else {
        Paths[x][y] = 1;
      }
    }
  }
}

bool Field::PathFinder(int startX, int startY, int endX, int endY) { 
  Paths[startX][startY] = 1;
  bool result = false;
  if (startX == endX and startY == endY) {
      return true;
  } else {
    if (startX - 1 >= 0 and Paths[startX - 1][startY] == 0) {
      result = result or PathFinder(startX - 1, startY, endX, endY);
    }
    if (startY - 1 >= 0 and Paths[startX][startY - 1] == 0) {
      result = result or PathFinder(startX, startY - 1, endX, endY);
    }
    if (startX + 1 < Width and Paths[startX + 1][startY] == 0) {
      result = result or PathFinder(startX + 1, startY, endX, endY);
    }
    if (startY + 1 < Height and Paths[startX][startY + 1] == 0) {
      result = result or PathFinder(startX, startY + 1, endX, endY);
    }
    return result;
  }
}

void Field::Click() {
  if (IsOver) {
    Restart();
    return;
  }
  if (CanAct) {
    if (HighlightedCelX >= 0 and HighlightedCelX < Width and
        HighlightedCelY >= 0 and HighlightedCelY < Height) {
      if (Bubbles[HighlightedCelX][HighlightedCelY]) {
        if (Bubbles[SelectedX][SelectedY]) {
          Bubbles[SelectedX][SelectedY]->SetSelection(false);
        }
        Bubbles[HighlightedCelX][HighlightedCelY]->SetSelection(true);
        SelectedX = HighlightedCelX;
        SelectedY = HighlightedCelY;
      } else {
        if (Bubbles[SelectedX][SelectedY]) {
          PathCleaner();
          if (PathFinder(SelectedX, SelectedY, HighlightedCelX,
                         HighlightedCelY)) {
            Bubbles[HighlightedCelX][HighlightedCelY] =
                Bubbles[SelectedX][SelectedY];
            Bubbles[HighlightedCelX][HighlightedCelY]->ChangeCoord(
                OffsetX + HighlightedCelX * CellSize + CellSize / 2,
                OffsetY + HighlightedCelY * CellSize + CellSize / 2);
            Bubbles[SelectedX][SelectedY] = nullptr;
            Bubbles[HighlightedCelX][HighlightedCelY]->SetSelection(false);
            CurrentCoords[0] = Vector2(HighlightedCelX, HighlightedCelY); 
            IsMoving = true;
            IsClicked = true;
            CanAct = false;
          }
        }
      }
    }
  }
}

void Field::ProcessInput() {
  int MouseX = GetMouseX() - OffsetX + CellSize;
  int MouseY = GetMouseY() - OffsetY + CellSize;
  HighlightedCelX = MouseX / CellSize - 1;
  HighlightedCelY = MouseY / CellSize - 1;
}

void Field::BubblesCreate() { 
    Bubble1 = Factory->CreateBubble();
  Bubble1->ChangeCoord(OffsetX + 700 + CellSize / 2, OffsetY + 200 + CellSize / 2);
    Bubble2 = Factory->CreateBubble();
  Bubble2->ChangeCoord(OffsetX + 700 + CellSize / 2,
                       OffsetY + 200 + CellSize + CellSize / 2);
    Bubble3 = Factory->CreateBubble();
  Bubble3->ChangeCoord(OffsetX + 700 + CellSize / 2,
                    OffsetY + 200 + CellSize*2 + CellSize / 2);
}

void Field::BubblesThrow() {
  if (!CanThrow) {
    return;
  }
  std::vector<int> FreeIDs;
  for (int x = 0; x < Width; x++) {
    for (int y = 0; y < Height; y++) {
      if (!Bubbles[x][y]) {
        FreeIDs.push_back(x+y*Height);
      }
    }
  }
  CanAct = false;
  if (FreeIDs.size() >= 3) {

    CanThrow = false;
    int ID = rand() % FreeIDs.size();
    int x = FreeIDs[ID];
    int y = x / Height;
    x = x % Height;
    Bubbles[x][y] = Bubble1;
    Bubble1->ChangeCoord(OffsetX + x * CellSize + CellSize / 2,
                      OffsetY + y * CellSize + CellSize / 2);
    FreeIDs.clear();
    for (int x = 0; x < Width; x++) {
      for (int y = 0; y < Height; y++) {
        if (!Bubbles[x][y]) {
          FreeIDs.push_back(x + y * Height);
        }
      }
    }
    CurrentCoords[0] = Vector2(x, y);
    
    ID = rand() % FreeIDs.size();
    x = FreeIDs[ID];
    y = y = x / Height;
    x = x % Height;
    Bubbles[x][y] = Bubble2;
    Bubble2->ChangeCoord(OffsetX + x * CellSize + CellSize / 2,
                      OffsetY + y * CellSize + CellSize / 2);
    FreeIDs.clear();
    for (int x = 0; x < Width; x++) {
      for (int y = 0; y < Height; y++) {
        if (!Bubbles[x][y]) {
          FreeIDs.push_back(x + y * Height);
        }
      }
    }
    CurrentCoords[1] = Vector2(x, y);
    
    ID = rand() % FreeIDs.size();
    x = FreeIDs[ID];
    y = y = x / Height;
    x = x % Height;
    Bubbles[x][y] = Bubble3;
    Bubble3->ChangeCoord(OffsetX + x * CellSize + CellSize / 2,
                      OffsetY + y * CellSize + CellSize / 2);
    FreeIDs.clear();
    for (int x = 0; x < Width; x++) {
      for (int y = 0; y < Height; y++) {
        if (!Bubbles[x][y]) {
          FreeIDs.push_back(x + y * Height);
        }
      }
    }
    CurrentCoords[2] = Vector2(x, y);
    IsMoving = true;

    BubblesCreate();
  } else {
    IsOver = true;
  }
}

void Field::Restart() {
  for (int x = 0; x < Width; x++) {
    for (int y = 0; y < Height; y++) {
      if (Bubbles[x][y]) {
        delete Bubbles[x][y];
      }
      Bubbles[x][y] = nullptr;
    }
  }
  Points = 0;
  CanAct = true;
  IsOver = false;
  BubblesThrow();
}

void Field::TickTimer() { 
  if (IsDelay) {
    DestroyDelay++;
    if (DestroyDelay == 30) {
      DestroyDelay = 0;
      IsDelay = false;
      CanAct = true;
      if (ThrowAfterDelay) {
        BubblesThrow();
        ThrowAfterDelay = false;
      }
    }
  }
  if (IsMoving) {
    MoveDelay++;
    if (MoveDelay == 30) {
      MoveDelay = 0;
      IsMoving = false;
      CanAct = true;
      if (IsClicked) {
        if (!Research(CurrentCoords[0].x, CurrentCoords[0].y)) {
          BubblesThrow();
        }
        IsClicked = false;
      } else {
        for (int i = 0; i < 3; i++) {
          int x = CurrentCoords[i].x;
          int y = CurrentCoords[i].y;
          Research(x, y);
        }
        std::vector<int> FreeIDs;
        for (int x = 0; x < Width; x++) {
          for (int y = 0; y < Height; y++) {
            if (!Bubbles[x][y]) {
              FreeIDs.push_back(x + y * Height);
            }
          }
        }
        if (FreeIDs.size() == 0) {
          IsOver = true;
        } else {
          CanThrow = true;
        }
      }
    }
  }
}

bool Field::Research(int X, int Y) { 
    raylib::Color Target = Bubbles[X][Y]->BubbleColor;
    bool flag = false,
            Worked = Search(X, Y, 1, 0, Target) or Search(X, Y, 0, 1, Target) or
                     Search(X, Y, 1, 1, Target) or Search(X, Y, 1, -1, Target);
    if (Worked) {
      CanAct = false;
      IsDelay = true;
      for (int x = 0; x < Width; x++) {
        for (int y = 0; y < Height; y++) {
          if (Bubbles[x][y]) {
            flag = true;
            break;
          }
        }
      }
      if (!flag) {
        ThrowAfterDelay = true;
      }
    }
    return Worked;
}

void Field::Destroy(int X, int Y, int XChange, int YChange, int ForawrdLength,
                    int BackwardLength) {
  int localX = X, localY = Y;
  for (int i = 0; i < ForawrdLength; i++) {
    if (Bubbles[localX][localY]) {
      Bubbles[localX][localY]->Destruct();
      Points += 100;
    }
    localX += XChange;
    localY += YChange;
  }
  localX = X, localY = Y;
  for (int i = 0; i < BackwardLength; i++) {
    localX -= XChange;
    localY -= YChange;
    if (Bubbles[localX][localY]) {
      Bubbles[localX][localY]->Destruct();
      Points += 100;
    }
  }
  if (Record < Points) {
    Record = Points;
    std::ofstream File("record.txt", std::ios::trunc);
    File << Record;
    File.close();
  }
  
}

bool Field::Search(int X, int Y, int XChange, int YChange, raylib::Color Target) { 
  int ForwardCount = 1, BackwardCount = 0, localX = X, localY = Y;
  bool flag = true;
  while (flag) {
    localX += XChange;
    localY += YChange;
    if (localX >= 0 and localX < Width and localY >= 0 and localY < Height and
        Bubbles[localX][localY] and
        Bubbles[localX][localY]->BubbleColor == Target) {
      ForwardCount++;
    } else {
      flag = false;
    }
    
  }
  localX = X, localY = Y;
  flag = true;
  while (flag) {
    localX -= XChange;
    localY -= YChange;
    if (localX >= 0 and localX < Width and localY >= 0 and localY < Height and
        Bubbles[localX][localY] and
        Bubbles[localX][localY]->BubbleColor == Target) {
      BackwardCount++;
    } else {
      flag = false;
    }
  }
  if (ForwardCount + BackwardCount >= 5) {
    Destroy(X, Y, XChange, YChange, ForwardCount, BackwardCount);
    return true;
  } else {
    return false;
  }
}
