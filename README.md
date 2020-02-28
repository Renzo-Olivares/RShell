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

Behind the scenes our `main` will instantiate our `ShellClient`. `ShellClient` will then instantiate the objects we need such as our `UserInput`, `Parser`, and `Executor`. `ShellClient` will then call its member function `init()` in a while loop that exits when the `Executor` returns the exitflag as true which is when it encounters the ExitCommand. The member function `init()` calls on our `UserInput` object that will prompt the user for input using the `$` and capture that input. `ShellClient` will then pass that raw input from `UserInput` into our `Parser`. Our `Parser` using regex(regular expressions) will then tokenize our raw input into tokens seperated by whitespace. Using these tokens `Parser` will sequentially transform them into a `BasicCommand`, `ExitCommand`, or `Connector` object depending on the situation and then push that object onto the a queue pf `Command`. Our `Parser` will then run `buildPrescedenceQueue()` which checks for parentheses and builds a new queue inserting parentheses. `Parser` then mirrors that output and passed it into `shuntingYard()` which turns the infix expression into postfix. After we have the postfix expression we use `buildTree()` which uses the postfix queue to build an expression tree. `ShellClient` will then pass the expression tree to the `Executor` where it will leverage `fork(), execvp(), and waitpid()` in order to execute the expression tree. The `Executor` will also take into account connector logic and will execute or skip commands as needed. `Executor` will execute the tree using in order traversal. `ShellClient` then checks if Executors exitflag is true, if it is then we exit the loop, if not then we continue and prompt the user once again for input.  

We will be using the composite pattern to represent our commands. Our client is our `ShellClient` and our component is `Command`. `Command` had three leaf nodes: `BasicCommand`, `Connector`, and `ExitCommand`.

Our `Parser` does most of its magic with regex. It seperates the string into tokens by whitespace using a regex pattern, however not whitespace in between quotations. We then loop through our matches keeping a count. If that count is 1 then the match but be an executable. If the count is 2 or greater it must be an argument. As long as it is an argument keep adding the matches together. Once we hit any type of `Connector` reset the count to 1 because after a `Connector` follows an executable. `Parser` also leverages helper functions like `characterize()` which turns a string into a `char*`, and `addTwoChars()` to add arguments, and `whitespaceTrimLt()` to trim trailing and leading whitespaces, and `commentTrim()` to trim the string of anything including and past a `#` not in between quotes.

#  Diagram 
![rshell_omt](images/rshellomt0213.jpg?raw=true)

# Classes
## Shell Client
* Instantiates UserInput to retrieve input from user
* Instantiates Parser and passes in input from UserInput
* Instantiates CommandQueue with return value of Parser(UserInput)
* Instantiates Executor and runs inOrder() to execute command tree built by Parser 
* Runs a loop until exit command is returned by Executor
```c++
class ShellClient{
	private:
		bool exit = false; //exit flag
	public:
		ShellClient();
		void init();
};
```

## UserInput
* Captures/prompts user for input
```c++
class UserInput{
	private:
		std::string rawInput;
	public:
		UserInput();
		std::string getInput(); //return raw input
};
```

## Parser
* Takes in user input and tokenizes it into seperate tokens:
	* Builds either BasicCommand, ExitCommand, or Connector(&& || ; ( )) depending on the conditions and pushes them onto a `queue` of Command pointers
* buildPrescedenceQueue() parses parentheses
* mirror() Mirrors queue of Command pointers and passes them to shuntingYard()
* shuntingYard() turns infix to postfix
* buildTree() Builds expression tree using Command* queue from postfix shuntingYard() output
* Saves expression tree root to Node*
```c++
class Parser{
	 private:
        std::queue<Command*> parsedCmds;
        std::string userInput;
		Node* cmndTree;
    public:
        Parser(std::string rawUserInput);
        void run(); //parser
        char* whitespaceTrimLt(std::string rawString); //trim leading and trailing whitespace
		char* characterize(std::string rawString); //turn string into char*
        void buildCmd(char* execu, char* args); //build command
		std::string commentTrim(std::string rawInput); //trim comment and everything after
		char* addTwoChars(Char* A, char* B); //add arguments
		std::queue<Command*> buildPrescedenceQueue(); //places parentheses in queue
		std::queue<Command*> mirror(std::queue<Command*>); //mirrors queue
		std::queue<Command*> shuntingYard(std::queue<Command*>); //infix to postfix
		void buildTree(std::queue);//postfix to expression tree
		Node* getParsedCmndTree();//returns expresssion tree
};
```

## Executor
* inOrder() : Takes in an expression tree and traverses through it in order until there are no more nodes, taking into account connectors.
* Leverages `fork(), execvp(), and waitpid()` to execute an expression tree using in order traversal.
* Handles connector precedence 
* Handles exit command
* Handles symbolic and literal test command
```c++
class Executor{
	private:
		int child_status;
		bool bracketError;
		bool andflag;
		bool orflag;
		bool exitflag;
	public:
		Executor();
		int runCmds(); //executes cmdList
		int getLastChildStatus(); //checks status of last child
		bool runTestCmd(Command* cmd); //runs test command
		void inOrder(Node* cmndNode); //executes tree in order
		bool isExit(); //returns exit flag
};
```

## Command
* `Command` Component with 3 leaves.
```c++
class Command{
	public:
		Command(){}
		virtual std::string cmdString(); //returns string with command/command details
		virtual char* getPath(); //returns path of command
		virtual char** getArgs(); //returns argument
        virtual std::vector<char*> getRawCmd(){}; //returns raw command vector of char* includes exec path and arguments
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
		const char* getPath();//returns executable path
		char* const* getArgs();//returns executable arguments
		virtual std::string cmdString();//returns string with command/command details
};
```

## Connector
* Inherits from `Command`
* Identifies `&&`, `||`, and `;`
```c++
class Connector: Public Command{
	private:
        std::string type;
    public:
        Connector(char* connectorType);
        char* getPath();
        char** getArgs();
        virtual std::string cmdString(); //returns connector type "&&"  or "||" or ";"
};
```
## ExitCommand
* Inherits from `Command`
* Exits rshell
```c++
class ExitCommand : public Command {
    private:
        std::string type;
    public:
        ExitCommand(char* exitex);
        char* getPath();
        char** getArgs();
        virtual std::string cmdString(); // returns "exit"
};
```

## Node
* Node object used to build expression tree
* Node value is of `Command*`
```c++
struct Node{
	Command* cmd;

	struct Node* left, *right;                   

	Node(Command* cmd){
		this->cmd = cmd;
		left = right = NULL;
	}
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
	* While still in the parent process we use `waitpid()` to pause the parent process until the child process exits
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
1. All issues closed.
