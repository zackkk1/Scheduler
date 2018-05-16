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
    std::vector<Shift *> Shifts;
  public:
    WorkScheduleError AddShift(Shift *NewShift);
    WorkScheduleError RemoveShift(Shift *ShiftToRemove);
    void WriteToFile(std::string Filename);
    void ReadFromFile(std::string Filename);
    Shift *GetCurrentShift();
};

#endif