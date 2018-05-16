#include "person.h"

std::string Person::GetName() {
    return this->Name;
}

void Person::SetName(std::string Name) {
    this->Name = Name;
}

ContactInformation Person::GetInformation() {
    return this->Information;
}