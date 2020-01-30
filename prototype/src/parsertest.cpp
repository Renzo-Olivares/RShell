/*
  Parser:
  [executable] [cmnd_args] [connector].....
  [executable]: before first space, right after a connector, or
  [cmnd_args]: can be inside " " or ' '
  [connector]: &&, ||, ;, not in between "" or ''
*/

//strip any whitespace from beginning of input
//command_args are in between " " or ' ' or in between a whitespace and a connector
//executable is after a connector or before the first whitespace in the string
//connector is && or || or ; not within a ' ' or " "
//original text(?=[^"]*(?:"[^"]*"[^"]*)*$)
/*
text            # match the literal characters 'text'
(?=             # start lookahead
   [^"]*          # match any number of non-quote characters
   (?:            # start non-capturing group, repeated zero or more times
      "[^"]*"       # one quoted portion of text
      [^"]*         # any number of non-quote characters
   )*             # end non-capturing group
   $              # match end of the string
)               # end lookahead
*/
//(?<AndConnector>&&(?=[^("|')]*(?:[("|')][^("|')]*[("|')][^("|')]*)*$))
//(?<SemiConnector>;(?=[^("|')]*(?:[("|')][^("|')]*[("|')][^("|')]*)*$))
//(?<OrConnector>\|\|(?=[^("|')]*(?:[("|')][^("|')]*[("|')][^("|')]*)*$))
#include <iostream>
#include <boost/regex.hpp>

int main(){
  std::string user_input;
  const char* andPatt = "(?<AndConnector>&&(?=[^(\"|')]*(?:[(\"|')][^(\"|')]*[(\"|')][^(\"|')]*)*$))";
  const char* orPatt = "(?<OrConnector>\\|\\|(?=[^(\"|')]*(?:[(\"|')][^(\"|')]*[(\"|')][^(\"|')]*)*$))";
  const char* semiPatt = "(?<SemiConnector>;(?=[^(\"|')]*(?:[(\"|')][^(\"|')]*[(\"|')][^(\"|')]*)*$))";
  const char *cmdPatt = "[\"'](.*?)[\"']";
  boost::regex andConnectorReg(andPatt);
  boost::regex orConnectorReg(orPatt);
  boost::regex semiConnectorReg(semiPatt);
  boost::regex cmdReg(cmdPatt);
  unsigned andCt = 0;
  unsigned orCt = 0;
  unsigned semiCt = 0;
  unsigned cmdCt = 0;

  std::cout << "Please enter a command" << std::endl;
  std::getline(std::cin, user_input);

  boost::sregex_token_iterator andToken(user_input.begin(), user_input.end(), andConnectorReg);
  boost::sregex_token_iterator andEnd;

  boost::sregex_token_iterator orToken(user_input.begin(), user_input.end(), orConnectorReg);
  boost::sregex_token_iterator orEnd;

  boost::sregex_token_iterator semiToken(user_input.begin(), user_input.end(), semiConnectorReg);
  boost::sregex_token_iterator semiEnd;

  boost::sregex_token_iterator cmdToken(user_input.begin(), user_input.end(), cmdReg);
  boost::sregex_token_iterator cmdEnd;

  while(andToken != andEnd){
      std::cout << *andToken++ << std::endl;
      andCt++;
  }

  while(orToken != orEnd){
      std::cout << *orToken++ << std::endl;
      orCt++;
  }

  while(semiToken != semiEnd){
      std::cout << *semiToken++ << std::endl;
      semiCt++;
  }

  while(cmdToken != cmdEnd){
      std::cout << *cmdToken++ << std::endl;
      cmdCt++;
  }

  std::cout << "There were " << andCt << " and tokens found." << std::endl;
  std::cout << "There were " << orCt << " or tokens found." << std::endl;
  std::cout << "There were " << semiCt << " semi tokens found." << std::endl;
  std::cout << "There were " << cmdCt << " command tokens found." << std::endl;

  std::cout << user_input << std::endl;
}