# CS 100 Programming Project
WINTER 2020
Phyllis Chen 862011526
Renzo Olivares 861156330

#Introduction
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

#Diagram


#Classes
##Parser
Takes in user input and determines executable paths and arguments. 

##Executer
Takes in executable path and arguments from Parser class.

##Connectors
This class will be a component with three child leaves.

##ConnectorAnd
One of three leaf classes, executes ";" and inherits from Connectors class.

##ConnectorOr
Another one of the three leaf classes, executes "||" and inherits from Connectors class.

##ConnectorSemiCol
Last of three leaf classes, executes "&&" and inherits from Connectors class.



#Prototypes/Research

#Development and Testing Roadmap


