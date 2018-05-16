#include <ctime>
#include <fstream>

#include "schedule.h"

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
        size_t ShiftLength = this->Shifts.size();
        Out.write((const char *)&ShiftLength, sizeof(size_t));
        for(std::vector<Shift *>::iterator it = this->Shifts.begin();
        it != this->Shifts.end(); ++it) {
            (*it)->WriteShift(&Out);
        }

        Out.close();
    }
}

void WorkSchedule::ReadFromFile(std::string Filename) {
    std::ifstream In(Filename, std::ofstream::binary);
    if(In.is_open()) {
        size_t ShiftLength;
        In.read((char *)&ShiftLength, sizeof(size_t));
        for(size_t i = 0; i < ShiftLength; i++) {
            Shift NewShift;
            unsigned long long Time;
            unsigned int Duration;

            In.read((char *)&Time, sizeof(Time));
            In.read((char *)&Duration, sizeof(Duration));

            Person *Assigned = new Person; 
            size_t PersonLength;
            In.read((char *)&PersonLength, sizeof(PersonLength));
            char *PersonData = new char[PersonLength];
            In.read(PersonData, sizeof(char) * PersonLength);

            //std::string copies byte data from PersonData, so we must call delete after.
            Assigned->SetName(std::string(PersonData, PersonLength));
            delete PersonData;

            NewShift.SetAssigned(Assigned);

            size_t PhoneNumberLength;
            In.read((char *)&PhoneNumberLength, sizeof(size_t));
            char *PhoneNumberData = new char[PhoneNumberLength];
            In.read(PhoneNumberData, sizeof(char) * PhoneNumberLength);

            Assigned->Information.PhoneNumber = std::string(PhoneNumberData, PhoneNumberLength);
            delete PhoneNumberData;

            size_t AddressLength;
            In.read((char *)&AddressLength, sizeof(size_t));
            char *AddressData = new char[AddressLength];
            In.read(AddressData, sizeof(char) * AddressLength);

            Assigned->Information.Address = std::string(AddressData, AddressLength);
            delete AddressData;

            size_t CityLength;
            In.read((char *)&CityLength, sizeof(size_t));
            char *CityData = new char[CityLength];
            In.read(CityData, sizeof(char) * CityLength);

            Assigned->Information.City = std::string(CityData, CityLength);
            delete CityData;

            size_t StateLength;
            In.read((char *)&StateLength, sizeof(size_t));
            char *StateData = new char[StateLength];
            In.read(StateData, sizeof(char) * StateLength);

            Assigned->Information.State = std::string(StateData, StateLength);
            delete StateData;

            size_t AvailableTimeLength;
            In.read((char *)&AvailableTimeLength, sizeof(size_t));
            for(size_t j = 0; j < AvailableTimeLength; j++) {
                size_t StartTime, EndTime;
                In.read((char *)StartTime, sizeof(unsigned int));
                In.read((char *)EndTime, sizeof(unsigned int));
                TimeSegment NewSegment(StartTime, EndTime);
                Assigned->Information.AvailableTime.insert(
                    Assigned->Information.AvailableTime.begin(), NewSegment);
            }

            this->Shifts.insert(this->Shifts.begin(), &NewShift);
        }
    }
}