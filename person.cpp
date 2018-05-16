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

ContactInformation Person::GetInformation() {
    return this->Information;
}