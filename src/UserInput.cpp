#include "../header/UserInput.hpp"

UserInput::UserInput(){
    std::cout << "$ ";
    std::getline(std::cin, rawInput);
}

std::string UserInput::getInput(){
    return rawInput;
}