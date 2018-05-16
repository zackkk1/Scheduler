#include <iostream>
#include "schedule.h"

const char *WelcomeMessage = "Welcome to Schedule Builder, this program is here to help you manager" \
" and build schedules. \nTo load an existing schedule pass the schedule as the first argument to this executable.\n" \
" e.g \"./main.exe schedule.sch\"";

enum CommandCode {
    Quit,
    Help,
    Unknown
};

CommandCode GetCommandCode(std::string const& InString) {
    if(InString == "quit") return Quit;
    if(InString == "help") return Help;
    return Unknown;
}

int main() {
    bool Running = true;
    WorkSchedule schedule;
    std::cout << WelcomeMessage << std::endl;
    while(Running) {
        std::string Command;
        std::cout << "> ";
        std::cin >> Command;
        std::cout << "You typed the command \"" << Command << "\"" << std::endl;
        switch(GetCommandCode(Command)) {
            case Quit:
                Running = false;
                break;
            case Help:
                break;
            default:
                std::cout << "Error command \"" << Command << "\" not found." << std::endl;
                break;
        }
    }

    return 0;
}