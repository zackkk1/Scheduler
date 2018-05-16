#include <ctime>
#include <fstream>

#include "schedule.h"

std::vector<Person *> WorkSchedule::GetPeople() {
    return this->People;
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

    this->Shifts.push_back(NewShift);
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
        size_t PeopleLength = this->People.size();
        Out.write((const char *)&PeopleLength, sizeof(size_t));
        for(std::vector<Person *>::iterator it = this->People.begin();
            it != this->People.end(); ++it) {
            (*it)->Write(&Out);
        }

        size_t ShiftLength = this->Shifts.size();
        Out.write((const char *)&ShiftLength, sizeof(size_t));
        for(std::vector<Shift *>::iterator it = this->Shifts.begin();
        it != this->Shifts.end(); ++it) {
            (*it)->Write(&Out);
        }

        Out.close();
    }
}

void WorkSchedule::ReadFromFile(std::string Filename) {
    std::ifstream In(Filename, std::ofstream::binary);
    if(In.is_open()) {
        size_t PeopleLength;
        In.read((char *)&PeopleLength, sizeof(size_t));
        for(size_t i = 0; i < PeopleLength; i++) {
            Person *NewPerson = new Person;

            size_t PersonLength;
            In.read((char *)&PersonLength, sizeof(PersonLength));
            char *PersonData = new char[PersonLength];
            In.read(PersonData, sizeof(char) * PersonLength);

            NewPerson->SetName(std::string(PersonData, PersonLength));
            delete PersonData;

            size_t PhoneNumberLength;
            In.read((char *)&PhoneNumberLength, sizeof(size_t));
            char *PhoneNumberData = new char[PhoneNumberLength];
            In.read(PhoneNumberData, sizeof(char) * PhoneNumberLength);

            NewPerson->Information.PhoneNumber = std::string(PhoneNumberData, PhoneNumberLength);
            delete PhoneNumberData;

            size_t AddressLength;
            In.read((char *)&AddressLength, sizeof(size_t));
            char *AddressData = new char[AddressLength];
            In.read(AddressData, sizeof(char) * AddressLength);

            NewPerson->Information.Address = std::string(AddressData, AddressLength);
            delete AddressData;

            size_t CityLength;
            In.read((char *)&CityLength, sizeof(size_t));
            char *CityData = new char[CityLength];
            In.read(CityData, sizeof(char) * CityLength);

            NewPerson->Information.City = std::string(CityData, CityLength);
            delete CityData;

            size_t StateLength;
            In.read((char *)&StateLength, sizeof(size_t));
            char *StateData = new char[StateLength];
            In.read(StateData, sizeof(char) * StateLength);

            NewPerson->Information.State = std::string(StateData, StateLength);
            delete StateData;

            size_t AvailableTimeLength;
            In.read((char *)&AvailableTimeLength, sizeof(size_t));
            for(size_t j = 0; j < AvailableTimeLength; j++) {
                size_t StartTime, EndTime;
                In.read((char *)StartTime, sizeof(unsigned int));
                In.read((char *)EndTime, sizeof(unsigned int));
                TimeSegment NewSegment(StartTime, EndTime);
                NewPerson->Information.AvailableTime.push_back(NewSegment);
            }

            this->People.push_back(NewPerson);
        }

        size_t ShiftLength;
        In.read((char *)&ShiftLength, sizeof(size_t));
        for(size_t i = 0; i < ShiftLength; i++) {
            Shift *NewShift = new Shift;
            unsigned long long Time;
            unsigned int Duration;
            int PersonIndex;

            In.read((char *)&Time, sizeof(Time));
            In.read((char *)&Duration, sizeof(Duration));
            In.read((char *)&PersonIndex, sizeof(PersonIndex));

            NewShift->SetAssignedIndex(PersonIndex);
            this->Shifts.push_back(NewShift);
        }
    }
}