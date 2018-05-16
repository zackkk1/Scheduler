#include "shift.h"
#include "person.h"

unsigned long long Shift::GetTime() {
    return this->Time;
}

unsigned int Shift::GetDuration() {
    return this->Duration;
}

void Shift::WriteShift(std::ofstream *Stream) {
    size_t NameLength, PhoneNumberLength, AddressLength, CityLength, StateLength, AvailableTimeLength;
    //Write Time and Duration
    Stream->write((const char *)&this->Time, sizeof(this->Time));
    Stream->write((const char *)&this->Duration, sizeof(this->Duration));

    //Write Person's name to file, need to prefix with the length first so we can read
    //that many bytes; do the same for each string.
    NameLength = this->Assigned->GetName().length();
    Stream->write((const char *)&NameLength, sizeof(size_t));
    Stream->write((const char *)this->Assigned->GetName().c_str(), sizeof(const char *) * NameLength);

    PhoneNumberLength = this->Assigned->GetInformation().PhoneNumber.length();
    Stream->write((const char *)&PhoneNumberLength, sizeof(size_t));
    Stream->write((const char *)this->Assigned->GetInformation().PhoneNumber.c_str(), sizeof(const char *) * PhoneNumberLength);

    AddressLength = this->Assigned->GetInformation().Address.length();
    Stream->write((const char *)&AddressLength, sizeof(size_t));
    Stream->write((const char *)this->Assigned->GetInformation().Address.c_str(), sizeof(const char *) * AddressLength);

    CityLength = this->Assigned->GetInformation().Address.length();
    Stream->write((const char *)&CityLength, sizeof(size_t));
    Stream->write((const char *)this->Assigned->GetInformation().City.c_str(), sizeof(const char *) * CityLength);

    StateLength = this->Assigned->GetInformation().Address.length();
    Stream->write((const char *)&StateLength, sizeof(size_t));
    Stream->write((const char *)this->Assigned->GetInformation().State.c_str(), sizeof(const char *) * StateLength);

    //Need to write the length of the vector so we can reconstruct it.
    AvailableTimeLength = this->Assigned->GetInformation().AvailableTime.size();
    Stream->write((const char *)&AvailableTimeLength, sizeof(size_t));
    for(std::vector<TimeSegment>::iterator it = this->Assigned->GetInformation().AvailableTime.begin();
        it != this->Assigned->GetInformation().AvailableTime.end(); ++it) {
        Stream->write((const char *)(*it).StartTime, sizeof((*it).StartTime));
        Stream->write((const char *)(*it).EndTime, sizeof((*it).EndTime));
    }
}

void Shift::SetAssigned(Person *Assigne) {
    this->SetAssigned(Assigne);
}