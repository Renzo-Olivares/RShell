#ifndef SHELLCLIENT_HPP
#define SHELLCLIENT_HPP

#include "../header/Executor.hpp"
#include "../header/Command.hpp"
#include "../header/BasicCommand.hpp"
#include "../header/Parser.hpp"
#include "../header/UserInput.hpp"
#include "../header/CommandQueue.hpp"

#include <queue>

class ShellClient {
    private:
        bool exit = false;
    public:
        ShellClient();
        void init();
};

#endif /* SHELLCLIENT_HPP */