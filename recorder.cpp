#include "recorder.h"

Recorder::Recorder() {
  std::fstream File("record.txt", std::ios::in);
  if (File >> Record) {}
  File.close();
}

void Recorder::Render() {
  
  DrawText(TextFormat("%08i", Points), 820, 80, 30, WHITE);
  DrawText(TextFormat("%08i", Record), 820, 525, 30, WHITE);
}

void Recorder::AddPoints(int points) { Points += points; }

void Recorder::Nullify() {
  if (Record < Points) {
    Record = Points;
  }
}

void Recorder::UpdateStatistic() {
  Nullify();
  std::ofstream File("record.txt", std::ios::trunc);
  File << Record;
  File.close();
}
