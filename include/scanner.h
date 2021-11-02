#ifndef SCANNER_H
#define SCANNER_H
#include "token.h"
#include<sstream>
#include<vector>
#include<unordered_map>
//Class to store a scanner class, which contains the functions used to parse a string into tokens
class Scanner{
	private:
		//The string to parse
		std::stringstream source;
		//The tokens contained in the string
		std::vector<Token> tokens;
		//Keeps track of the current line
		int line;
		//Scan only the next token and appends it to tokens
		void scanNextToken();
		//Add the next token to the vector tokens
		void addToken(TokenType t);
		//This method is for the case of strings, for example
		void addToken(TokenType t, std::string s);
		//This method is for the case of numbers
		void addToken(TokenType t,double d);
		//See if the next character on source matches c. If it does, reads the character
		bool match(char c);
		//Create a string token after reading a '"' and adds to tokens
		void string();
		//Create a token for number literals and adds to tokens
		//It doesnt support a leading decimal point
		void number();
		//Create a token for identifiers and add to tokens
		void identifier();
		//Returns the character two positions ahead of source
		char peekNext();
	public:
		//Constructor
		Scanner(std::string source);
		//Scan the tokens into tokens and return the vector
		std::vector<Token> scanTokens();	
};

//The map with the language's reserved words
const std::unordered_map <std::string,TokenType> keywords={
{"and", AND},
{"class", CLASS},
{"else", ELSE},
{"false", FALSE},
{"for", FOR },
{"fun", FUN },
{"if", IF },
{"nil", NIL },
{"or", OR },
{"print", PRINT },
{"return", RETURN },
{"super", SUPER },
{"this", THIS },
{"true", TRUE },
{"var", VAR },
{"while", WHILE }
};

#endif



