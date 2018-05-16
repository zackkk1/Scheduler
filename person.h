#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include <fstream>

class TimeSegment {
  public:
    TimeSegment(unsigned int StartTime, unsigned int EndTime);
    unsigned int StartTime;
    unsigned int EndTime;
};

class ContactInformation {
  public:
    std::string PhoneNumber;
    std::string Address;
    std::string City;
    std::string State;
    std::vector<TimeSegment> AvailableTime;
};

class Person {
  private:
    std::string Name;
  public:
    ContactInformation Information;
    std::string GetName(void);
    void SetName(std::string Name);
    void Write(std::ofstream *Stream);
    ContactInformation GetInformation(void);
};

#endif