#ifndef SHIFT_H
#define SHIFT_H

#include <fstream>
#include "person.h"

class Shift {
  private:
    unsigned long long Time;
    unsigned int Duration;
    Person *Assigned;
  public:
    unsigned long long GetTime(void);
    void SetTime(unsigned long long Time);
    unsigned int GetDuration(void);
    Person *GetAssigned(void);
    void SetDuration(unsigned long long Duration);
    void SetAssigned(Person *Assigne);
    void WriteShift(std::ofstream *Stream);
};

#endif