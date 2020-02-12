#ifndef USERINPUT_HPP
#define USERINPUT_HPP

#include <iostream>

class UserInput {
    private:
        std::string rawInput;
    public:
        UserInput();
        std::string getInput();
};

#endif /* USERINPUT_HPP */