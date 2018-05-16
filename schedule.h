#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include <string>

#include "shift.h"

enum class WorkScheduleError {
    ErrorOk = 0,
    ErrorShiftConflict,
    ErrorNoShift
};

class WorkSchedule {
  private:
    std::vector<Person *> People;
    std::vector<Shift *> Shifts;
  public:
    WorkScheduleError AddShift(Shift *NewShift);
    WorkScheduleError RemoveShift(Shift *ShiftToRemove);
    std::vector<Person *> GetPeople();
    void WriteToFile(std::string Filename);
    void ReadFromFile(std::string Filename);
    Shift *GetCurrentShift();
};

#endif