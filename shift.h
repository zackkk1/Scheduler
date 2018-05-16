#ifndef SHIFT_H
#define SHIFT_H

#include <fstream>
#include "person.h"

class Shift {
  private:
    unsigned long long Time;
    unsigned int Duration;
    int AssignedIndex;
  public:
    unsigned long long GetTime(void);
    void SetTime(unsigned long long Time);
    unsigned int GetDuration(void);
    int GetAssignedIndex(void);
    void SetDuration(unsigned long long Duration);
    void SetAssignedIndex(int AssignedIndex);
    void Write(std::ofstream *Stream);
};

#endif