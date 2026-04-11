#pragma once
#include <fstream>
#include <iostream>

#include "raylib-cpp.hpp"

class Recorder {
 public:
  Recorder();
  std::fstream* File;
  int Points = 0, Record = 0;
  void Render();
  void AddPoints(int points);
  void Nullify();
  void UpdateStatistic();
};