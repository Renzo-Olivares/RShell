# CS 100 Programming Project
WINTER 2020

Phyllis Chen 862011526

Renzo Olivares 861156330


# Introduction
This is a command shell, and executes commands such as:
* Prints a command prompt $
	* ex. $ `executable [argumentList][connector][executable]`
* Commands and connectors
	* &&: next command executes only if the first one executes
	* ||: next command executes only if the first one fails
	*  ;: next command is always executed
* Executes the appropriate commands using fork, execvp, and waitpid
* Everything after # is a comment
* Exits program when command is executed.

We will be using the composite pattern to represent commands and operators.


#  Diagram


# Classes
## Shell Client
* Instantiates UserInput to retrieve input from user
* Instantiates CommandQueue with return value of Parser(UserInput)
* Instantiates Executor and passes in CommandQueue to be executed
```c++
class ShellClient{
	public:
		ShellClient(){
			UserInput rawInput = UserInput();
			Executor runner = Executor()
			Parser analyzer = Parser();
			CommandQueue parsedCmnds = CommandQueue();

			while(rawInput is not exit command){
				rawInput.capture();
				analyzer.input(rawInput);
				parsedCmnds.add(analyzer.run());
				runner.add(parsedCmnds);
				runner.run();
			}
		}
};
```

## UserInput
* Captures/prompts user for input
```c++
class UserInput{
	private:
		std::string rawInput;
	public:
		UserInput(){}
		void capture(std::string userInput){}
		std::string getRaw(){return rawInput;}
};
```

## Parser
* Takes in user input and tokenizes it into seperate tokens:
	* ExecToken -> Along with ArgsToken gets transformed into BasicCommand object
	* ArgsToken -> Along with ExecToken gets transformed into BasicCommand object
	* AndToken -> Becomes ConnectorAnd object
	* OrToken -> Becomes ConnectorOr object
	* SemiToken -> Becomes ConnectorSemiColon object
* Runs analysis and returns a queue of Command objects that the Executor can run
```c++
class Parser{
		std::string targetString;
	public:
		Parser(){}
		void input(UserInput rawInput){};
		queue run(){}
};
```

## Executor
* Takes in a CommandQueue and loops through it until it is empty.
* Leverages fork(), execvp(), and waitpid() to run CommandQueue.
* Handles connector precedence 
```c++
class Executor{
	private:
		CommandQueue cmdList;
	public:
		Executor(){}
		void add(){} //adds commands to cmdList
		void run(){} //executes cmdList
};
```

## Command
* Command Component with 5 leaves.
```c++
class Command{
	public:
		Command(){}
		virtual std::string showCmndDetails(){} //returns string with command/command details
};
```

## BasicCommand
* Inherits from Command
* Object with attributes for a basic command. 
```c++
class BasicCommand: Public Command{
	private:
		const char* execp;  //executable path
		char* const* args; //executable arguments
	public:
		BasicCommand(){}
		const char* getPath(){return execp;} //returns executable path
		char* const* getArgs(){return args;} //returns executable arguments
		virtual std::string showCmndDetails(){} //returns string with command/command details
};
```

## CommandQueue
* Inherits from Command
* Stores a queue of Command objects to be passed to the Executor for execution.
```c++
class CommandQueue: Public Command{
	private:
		queue<Command> cmndLine;
	public:
		CommandQueue(){}
		void addToQueue(){cmdLine.push();}
		void popFromQueue(){cmdLine.pop();}
		virtual std::string showCmndDetails(){} //returns string with command/command details

};
```

## ConnectorAnd
* Inherits from Command
* Identifies "&&".
```c++
class ConnectorAnd: Public Command{
	public:
		ConnectorAnd(){}
		virtual std::string showCmndDetails(){} //returns string with command/command details
};
```

## ConnectorOr
* Inherits from Command
* Identifies "||".
```c++
class ConnectorOr: Public Command{
	public:
		ConnectorOr(){}
		virtual std::string showCmndDetails(){} //returns string with command/command details
};
```

## ConnectorSemiCol
* Inherits from Command
* Identifies ";".
```c++
class ConnectorSemiCol: Public Command{
	public:
		ConnectorSemiCol(){}
		virtual std::string showCmndDetails(){} //returns string with command/command details
};
```


# Prototypes/Research


# Development and Testing Roadmap


