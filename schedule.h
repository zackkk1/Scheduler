#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include <string>

enum class WorkScheduleError {
    ErrorOk = 0,
    ErrorShiftConflict,
    ErrorNoShift
};

class TimeSegment {
    unsigned int StartTime;
    unsigned int EndTime;
};

class ContactInformation {
    std::string PhoneNumber;
    std::string Address;
    std::string City;
    std::string State;
    std::vector<TimeSegment> AvailableTime;
};

class Person {
  private:
    std::string Name;
    ContactInformation Information;
  public:
    std::string GetName(void);
    ContactInformation GetInformation(void);
};

std::string Person::GetName() {
    return this->Name;
}

ContactInformation Person::GetInformation() {
    return this->Information;
}

class Shift {
  private:
    unsigned long long Time;
    unsigned int Duration;
    Person *Assigned;
  public:
    unsigned long long GetTime(void);
    unsigned int GetDuration(void);
    void WriteShift(std::ofstream Stream);
};

class WorkSchedule {
  private:
    std::vector<Shift *> Shifts;
  public:
    WorkScheduleError AddShift(Shift *NewShift);
    WorkScheduleError RemoveShift(Shift *ShiftToRemove);
    void WriteToFile(std::string Filename);
    Shift *GetCurrentShift();
};

#endif