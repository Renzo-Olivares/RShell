#include "../header/UserInput.hpp"

UserInput::UserInput(){
    std::string rawInput;
    std::cout << "$ ";
    std::getline(std::cin, rawInput);
    std::cout <<  rawInput << std::endl;
}