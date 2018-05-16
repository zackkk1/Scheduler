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
    Unknown
};

CommandCode GetCommandCode(std::string const& InString) {
    if(InString == "quit") return Quit;
    if(InString == "help") return Help;
    if(InString == "nshift") return NewShift;
    if(InString == "nperson") return NewPerson;
    return Unknown;
}

Shift *NewShiftFromUser(void) {
    return nullptr;
}

Person *NewPersonFromUser(void) {
    std::cout << "What is this person's first name? ";
    
    return nullptr;
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
        //Load file here.
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

                Shift *NewShift = NewShiftFromUser();
                if(NewShift != nullptr) {
                    Scheudle.AddShift(NewShift);
                } else {
                    std::cout << "Aborting creation of new shift." << std::endl;
                }
            } break;
            case NewPerson: {

            } break;
            default:
                std::cout << "Error command \"" << Command << "\" not found." << std::endl;
                break;
        }
    }

    return 0;
}