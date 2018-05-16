#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>

class TimeSegment {
  public:
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
    ContactInformation Information;
  public:
    std::string GetName(void);
    void SetName(std::string Name);
    ContactInformation GetInformation(void);
};

#endif