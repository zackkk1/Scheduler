#include "person.h"

TimeSegment::TimeSegment(unsigned int StartTime, unsigned int EndTime) {
    this->StartTime = StartTime;
    this->EndTime = EndTime;
}

std::string Person::GetName() {
    return this->Name;
}

void Person::SetName(std::string Name) {
    this->Name = Name;
}

void Person::Write(std::ofstream *Stream) {
    size_t NameLength = this->GetName().length();
    Stream->write((const char *)&NameLength, sizeof(size_t));
    Stream->write((const char *)this->GetName().c_str(), sizeof(const char) * NameLength);

    size_t PhoneNumberLength = this->GetInformation().PhoneNumber.length();
    Stream->write((const char *)&PhoneNumberLength, sizeof(size_t));
    Stream->write((const char *)this->GetInformation().PhoneNumber.c_str(), sizeof(const char) * PhoneNumberLength);

    size_t AddressLength = this->GetInformation().Address.length();
    Stream->write((const char *)&AddressLength, sizeof(size_t));
    Stream->write((const char *)this->GetInformation().Address.c_str(), sizeof(const char) * AddressLength);

    size_t CityLength = this->GetInformation().Address.length();
    Stream->write((const char *)&CityLength, sizeof(size_t));
    Stream->write((const char *)this->GetInformation().City.c_str(), sizeof(const char) * CityLength);

    size_t StateLength = this->GetInformation().Address.length();
    Stream->write((const char *)&StateLength, sizeof(size_t));
    Stream->write((const char *)this->GetInformation().State.c_str(), sizeof(const char) * StateLength);

    size_t AvailableTimeLength = this->GetInformation().AvailableTime.size();
    Stream->write((const char *)&AvailableTimeLength, sizeof(size_t));
    for(std::vector<TimeSegment>::iterator it = this->GetInformation().AvailableTime.begin();
        it != this->GetInformation().AvailableTime.end(); ++it) {
        Stream->write((const char *)(*it).StartTime, sizeof((*it).StartTime));
        Stream->write((const char *)(*it).EndTime, sizeof((*it).EndTime));
    }
}

ContactInformation Person::GetInformation() {
    return this->Information;
}