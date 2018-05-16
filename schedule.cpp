#include <ctime>
#include <fstream>

#include "schedule.h"

unsigned long long Shift::GetTime() {
    return this->Time;
}

unsigned int Shift::GetDuration() {
    return this->Duration;
}

WorkScheduleError WorkSchedule::RemoveShift(Shift *ShiftToRemove) {
    for(std::vector<Shift *>::iterator it = this->Shifts.begin();
        it != this->Shifts.end(); ++it) {
        if(ShiftToRemove->GetTime() == (*it)->GetTime() &&
            ShiftToRemove->GetDuration() == (*it)->GetDuration()) {
            this->Shifts.erase(it);
            return WorkScheduleError::ErrorOk;
        }

    }

    return WorkScheduleError::ErrorNoShift;
}

WorkScheduleError WorkSchedule::AddShift(Shift *NewShift) {
    for(std::vector<Shift *>::iterator it = this->Shifts.begin();
        it != this->Shifts.end(); ++it) {
        if(NewShift->GetTime() >= (*it)->GetTime() &&
            NewShift->GetTime()  <= ((*it)->GetTime() + (*it)->GetDuration())) {
            return WorkScheduleError::ErrorShiftConflict;
        }
    }

    this->Shifts.insert(this->Shifts.begin(), NewShift);
    return WorkScheduleError::ErrorOk;
}

Shift *WorkSchedule::GetCurrentShift() {
    //Have to be careful here, time_t on posix systems is an integral value,
    //but this may not always be the case, for now most implementations treat
    //the return value as time since epoch.

    time_t TimeNow = std::time(nullptr);
    long long CurrentUnixTime = static_cast<unsigned long long>(TimeNow);

    for(std::vector<Shift *>::iterator it = this->Shifts.begin();
        it != this->Shifts.end(); ++it) {
        if(CurrentUnixTime >= (*it)->GetTime() &&
            CurrentUnixTime <= ((*it)->GetTime() + (*it)->GetDuration())) {
            return *it;
        }
    }

    return nullptr;
}

void WorkSchedule::WriteToFile(std::string Filename) {
    std::ofstream Out(Filename, std::ofstream::binary);
    if(Out.is_open()) {
        for(std::vector<Shift *>::iterator it = this->Shifts.begin();
        it != this->Shifts.end(); ++it) {
            (*it)->WriteShift(Out);
        }

        Out.close();
    }
}

void Shift::WriteShift(std::ofstream Stream) {
    //Write Time and Duration
    Stream.write((const char *)&this->Time, sizeof(this->Time));
    Stream.write((const char *)&this->Duration, sizeof(this->Duration));

    //Write Person's name to file, need to prefix with the length first so we can read
    //that many bytes.
    int NameLength = this->Assigned->GetName().length;
    Stream.write((const char *)&NameLength, sizeof(NameLength));
    Stream.write((const char *)this->Assigned->GetName().c_str(), sizeof(const char *) * NameLength);

    //Write Contact Information
    
}