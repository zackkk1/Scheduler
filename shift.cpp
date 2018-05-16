#include "shift.h"
#include "person.h"

unsigned long long Shift::GetTime() {
    return this->Time;
}

unsigned int Shift::GetDuration() {
    return this->Duration;
}

int Shift::GetAssignedIndex() {
    return this->AssignedIndex;
}

void Shift::Write(std::ofstream *Stream) {
    Stream->write((const char *)&this->Time, sizeof(this->Time));
    Stream->write((const char *)&this->Duration, sizeof(this->Duration));
    Stream->write((const char *)&this->AssignedIndex, sizeof(this->AssignedIndex));
}

void Shift::SetAssignedIndex(int PersonIndex) {
    this->AssignedIndex = PersonIndex;
}