#ifndef CONNECTOR_HPP
#define CONNECTOR_HPP

#include "../header/Command.hpp"

class Connector : public Command {
    private:
        std::string type;
    public:
        Connector(char* connectorType);
        char* getPath();
        char** getArgs();
        bool isMultiple();
        virtual std::string cmdString();
};

#endif /* CONNECTOR_HPP */