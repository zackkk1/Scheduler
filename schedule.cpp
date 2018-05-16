#include <iostream>
#include <vector>
using  namespace std;

class TimeSegment {
    unsigned int StartTime;
    unsigned int EndTime;
};

class ContactInformation {
    string PhoneNumber;
    string Address;
    string City;
    string State;
    vector<TimeSegment> AvailableTime;
};

class Person {
    string Name;
    ContactInformation Information;
};

class Shifts {
    unsigned int Time;
    unsigned int Duration;
    Person *Assigned;
};

class WorkSchedule {
    vector<Shifts> Shifts;
};

int main() {
    return 0;
}