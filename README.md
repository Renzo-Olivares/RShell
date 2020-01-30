# CS 100 Programming Project
WINTER 2020

Phyllis Chen 862011526

Renzo Olivares 861156330


# Introduction
This is a command shell, and executes commands such as:
* Prints a command prompt $
	* ex. $ `[executable] [argumentList] [connector] [executable]....`
* Commands and connectors
	* `&&`: next command executes only if the first one executes
	* `||`: next command executes only if the first one fails
	* `;`: next command is always executed
* Leverages `fork(), execvp(), waitpid()` to execute a queue of commands
* Everything after `#` is a comment.
* Exits program when exit command is executed.

User will launch Rshell with
```
./rshell
```
They will then be prompted for input as follows
```
$
```

Behind the scenes our `main` will instantiate our `ShellClient`. `ShellClient` will then instantiate the objects we need such as our `UserInput`, `Parser`, `CommandQueue`, and `Executor`. `ShellClient` will then call on our `UserInput` object that will prompt the user for input using the `$` and capture that input. `ShellClient` will then pass that raw input from `UserInput` into our `Parser`. Our `Parser` using regex(regular expressions) will then tokenize our raw input into tokens such as ExecToken, ArgsToken, AndToken, OrToken, and SemiToken. Using these tokens `Parser` will sequentially transform ExecToken and ArgsToken into a `BasicCommand` object and then push that object onto the `CommandQueue`. Similarly, AndToken, OrToken, and SemiToken will be individually transformed into their corresponding `Connector` object and also pushed onto the `CommandQueue`. `ShellClient` will then pass the `CommandQueue` into the `Executor` where it will leverage `fork(), execvp(), and waitpid()` in order to execute the `CommandQueue`. The `Executor` will also take into account connector prescedence and will execute or skip commands as needed.  

We will be using the composite pattern to represent our commands. Our client is our `ShellClient` and our component is `Command`. `Command` had four leaf nodes: `ConnectorAnd`, `ConnectorOr`, and `ConnectorSemiColon`, and `BasicCommand`. `Command` also has a composite which is our `CommandQueue`. 


#  Diagram
![rshell_omt](images/rshell_omt.jpg?raw=true)

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
	* ExecToken -> Along with ArgsToken gets transformed into `BasicCommand` object
	* ArgsToken -> Along with ExecToken gets transformed into `BasicCommand` object
	* AndToken -> Becomes `ConnectorAnd` object
	* OrToken -> Becomes `ConnectorOr` object
	* SemiToken -> Becomes `ConnectorSemiColon` object
* Runs analysis and returns a `queue` of `Command` objects that the Executor can run
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
* Takes in a `CommandQueue` and loops through it until it is empty.
* Leverages `fork(), execvp(), and waitpid()` to run `CommandQueue`.
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
* `Command` Component with 5 leaves.
```c++
class Command{
	public:
		Command(){}
		virtual std::string showCmndDetails(){} //returns string with command/command details
};
```

## BasicCommand
* Inherits from `Command`
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
* Inherits from `Command`
* Stores a `queue` of `Command` objects to be passed to the `Executor` for execution.
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
* Inherits from `Command`
* Identifies `&&`.
```c++
class ConnectorAnd: Public Command{
	public:
		ConnectorAnd(){}
		virtual std::string showCmndDetails(){} //returns string with command/command details
};
```

## ConnectorOr
* Inherits from `Command`
* Identifies `||`.
```c++
class ConnectorOr: Public Command{
	public:
		ConnectorOr(){}
		virtual std::string showCmndDetails(){} //returns string with command/command details
};
```

## ConnectorSemiCol
* Inherits from `Command`
* Identifies `;`.
```c++
class ConnectorSemiCol: Public Command{
	public:
		ConnectorSemiCol(){}
		virtual std::string showCmndDetails(){} //returns string with command/command details
};
```


# Prototypes/Research
* `fork()` : 
	* Creates new child process
	* If value is `0` then we are in the child process
	* If value is not `0` then we are in the parent
	* If value is `-1` then our fork failed to create a new child process
* `execvp(const char* exec, char* const args)` : 
	* Function responsible for executing command based on an executable path and arguments
	* Only returns if an error has occured
* `waitpid(pid_t pid, int *status, int options)` : 
	* `pid` can be :
		* `-1` : wait for any child process
		* `0` : wait for child process whose ID is equal to calling process
		* any number less than -1 or greater than 0 indicating the child process ID
	* `status` will be the exit status of the child process
	* `options` :
		* `WNOHANG` : return immediately if no child exited
		* `WUNTRACED` : return if child has stopped but not traced by `ptrace()`
		* `WCONTINUED` : return if stopped child is resumed as a result of delivery of `SIGCONT`
	* Returns PID of the exited child process
	* `status` is written with exit status of exited child process
* Leveraging `fork(), execvp(), and waitpid()` :
	* We use `fork()` to create a new child process
	* While still in the child process we use `waitpid()` to pause the parent process until the child process exits
	* Now in the child process we can call on `execvp()` to execute our command by passing it an executable path i.e. `ls` and arguments i.e. `-a` to run `ls -a`
	* If `execvp()` completes succesfully it will return nothing, and go back to the parent process, if it fails it will return an exit status of `256`
	* Back at the parent process `waitpid()` has now given us the exited child process's PID and exit status
* Regex(regular expressions) :
	* We can use Boost library to leverage regex in our project
	* Another option is to use the built in regex library provided by C++ 11
	* Regex is a powerful tool used to filter/identify patterns in text
	* We want to leverage regex in our project to identify certain tokens in ou raw user input. We then want to transform our raw user input into `BasicCommand` objects and `Connectors` that will be pushed onto a `CommandQueue` where they will be executed FIFO by the `Executor`
	* Potential regex patterns:
		* To identify AndConnector: `(?<AndConnector>&&(?=[^("|')]*(?:[("|')][^("|')]*[("|')][^("|')]*)*$))`
		* To indetify SemiColonConnector: `(?<SemiConnector>;(?=[^("|')]*(?:[("|')][^("|')]*[("|')][^("|')]*)*$))`
		* To identify OrConnector: `(?<OrConnector>\|\|(?=[^("|')]*(?:[("|')][^("|')]*[("|')][^("|')]*)*$))`
		* To identify arguments between quotes: `(?<Args>[\"'](.*?)[\"'])`


# Development and Testing Roadmap
1. `ShellClient`
	* [#1 Develop ShellClient](https://github.com/cs100/assignment-renzo_phyllis/issues/1)
	* [#11 Unit & Integration Tests](https://github.com/cs100/assignment-renzo_phyllis/issues/11)
2. `UserInput`
	* [#2 Develop UserInput](https://github.com/cs100/assignment-renzo_phyllis/issues/2)
	* [#12 Unit & Integration Tests](https://github.com/cs100/assignment-renzo_phyllis/issues/12)
2. `Command`
	* [#6 Develop Command](https://github.com/cs100/assignment-renzo_phyllis/issues/6)
	* [#16 Unit & Integration Tests](https://github.com/cs100/assignment-renzo_phyllis/issues/16)
3. `BasicCommand`
	* [#10 Develop BasicCommand](https://github.com/cs100/assignment-renzo_phyllis/issues/10)
	* [#20 Unit & Integration Tests](https://github.com/cs100/assignment-renzo_phyllis/issues/20)
4. `CommandQueue`
	* [#5 Develop CommandQueue](https://github.com/cs100/assignment-renzo_phyllis/issues/5)
	* [#15 Unit & Integration Tests](https://github.com/cs100/assignment-renzo_phyllis/issues/15)
5. `ConnectorAnd`
	* [#7 Develop ConnectorAnd](https://github.com/cs100/assignment-renzo_phyllis/issues/7)
	* [#17 Unit & Integration Tests](https://github.com/cs100/assignment-renzo_phyllis/issues/17)
6. `ConnectorOr`
	* [#8 Develop ConnectorOr](https://github.com/cs100/assignment-renzo_phyllis/issues/8)
	* [#18 Unit & Integration Tests](https://github.com/cs100/assignment-renzo_phyllis/issues/18)
7. `ConnectorSemiColon`
	* [#9 Develop ConnectorSemiColon](https://github.com/cs100/assignment-renzo_phyllis/issues/9)
	* [#19 Unit & Integration Tests](https://github.com/cs100/assignment-renzo_phyllis/issues/19)
8. `Parser`
	* [#3 Develop Parser](https://github.com/cs100/assignment-renzo_phyllis/issues/3)
	* [#14 Unit & Integration Tests](https://github.com/cs100/assignment-renzo_phyllis/issues/14)
9. `Executor`
	* [#4 Develop Executor](https://github.com/cs100/assignment-renzo_phyllis/issues/4)
	* [#13 Unit & Integration Tests](https://github.com/cs100/assignment-renzo_phyllis/issues/13)

