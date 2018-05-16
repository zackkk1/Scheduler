#include <iostream>
#include "schedule.h"

const char *WelcomeMessage = "Welcome to Schedule Builder, this program is here to help you manager" \
" and build schedules. \nTo load an existing schedule pass the schedule as the first argument to this executable.\n" \
" e.g \"./main.exe schedule.sch\"\n Type \"help\" to get started with some commands.";

enum CommandCode {
    Quit,
    Help,
    NewShift,
    NewPerson,
    Save,
    Unknown
};

CommandCode GetCommandCode(std::string const& InString) {
    if(InString == "quit") return Quit;
    if(InString == "help") return Help;
    if(InString == "nshift") return NewShift;
    if(InString == "nperson") return NewPerson;
    if(InString == "save") return Save;
    return Unknown;
}

Shift *NewShiftFromUser(WorkSchedule *const Schedule) {
    Shift *NewShift = new Shift;
    std::cout << "First you need to select the person's index, I will list them for you." << std::endl;
    Schedule->PrintPeople();
    std::cout << std::endl;

    int Index;
    std::cout << "What is the desired person's index? ";
    std::cin >> Index;

    NewShift->SetAssignedIndex(Index);

    unsigned long long Time;
    unsigned int Duration;
    std::cout << "What time do they start? ";
    std::cin >> Time;

    std::cout << "What is their duration? ";
    std::cin >> Duration;

    NewShift->SetTime(Time);
    NewShift->SetDuration(Duration);
    return NewShift;
}

Person *NewPersonFromUser(void) {
    Person *NewPerson = new Person;
    std::string FirstName, LastName;
    std::cout << "What is this person's first name? ";
    std::cin >>FirstName;
    std::cout << "What is this person's last name? ";
    std::cin >>LastName;

    NewPerson->SetName(FirstName + " " + LastName);
    return NewPerson;
}

void PrintHelp(void) {
    std::cout << "Available Commands:" << std::endl;
    std::cout << "\tquit\t to quit the program." << std::endl;
    std::cout << "\thelp\t to print program help." << std::endl;
    std::cout << "\tnshift\t to create a new shift." << std::endl;
    std::cout << "\tnperson\t to create a new person." << std::endl;
}

int main(int argc, char **argv) {
    bool Running = true;
    WorkSchedule Scheudle;
    if(argc > 1) {
        Scheudle.ReadFromFile(argv[1]);
    }

    std::cout << WelcomeMessage << std::endl;
    while(Running) {
        std::string Command;
        std::cout << "> ";
        std::cin >> Command;
        //std::cout << "You typed the command \"" << Command << "\"" << std::endl;
        switch(GetCommandCode(Command)) {
            case Quit:
                Running = false;
                break;
            case Help:
                PrintHelp();
                break;
            case NewShift: {
                if(Scheudle.GetPeople().size() == 0) {
                    std::cout << "Before you add a new shift, you need to add a new Person to the list of " \
                    "available people. Type \"nperson\" to create a new person first." << std::endl;
                    break;
                }

                Shift *NewShift = NewShiftFromUser(&Scheudle);
                if(NewShift != nullptr) {
                    Scheudle.AddShift(NewShift);
                } else {
                    std::cout << "Aborting creation of new shift." << std::endl;
                }
            } break;
            case NewPerson: {
                Person *NewPerson = NewPersonFromUser();
                if(NewPerson != nullptr) {
                    Scheudle.AddPerson(NewPerson);
                } else {
                    std::cout << "Aborting creation of new person." << std::endl;
                }
            } break;
            case Save: {
                Scheudle.WriteToFile("schedule.sch");
                std::cout << "Wrote to file \"schedule.sch\"" << std::endl;
            } break;
            default:
                std::cout << "Error command \"" << Command << "\" not found." << std::endl;
                break;
        }
    }

    return 0;
}