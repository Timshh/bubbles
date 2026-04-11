#include "gamemode.h"

Gamemode::Gamemode(int width, int height, raylib::Texture* bground,
                   raylib::Texture* gameover, raylib::Texture* recordimage,
                   raylib::Texture* pointsimage) {
  InitAudioDevice();
  Width = width;
  Height = height;
  Factory = new BubbleFactory();
  Record = new Recorder();
  PlayField = new Field(width, height, Factory, Record);
  PlayField->BubblesCreate();
  PlayField->BubblesThrow();
  BgImage = bground;
  Gameover = gameover;
  RecordImage = recordimage;
  PointsImage = pointsimage;
}

Gamemode::~Gamemode() {}

void Gamemode::Render() {
  BgImage->Draw(1100 - BgImage->GetWidth(), 850 - BgImage->GetHeight());
  RecordImage->Draw(690, 400);
  PointsImage->Draw(690, -50);
  PlayField->ProcessInput();
  PlayField->Render();
  Record->Render();
  if (PlayField->State == FieldState::GameOver) {
    Gameover->Draw(0, 0);
  }
}