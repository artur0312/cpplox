#ifndef TOKEN_H
#define TOKEN_H

#include<iostream>
#include<string>
#include<vector>
//The different kinds of tokens
enum TokenType{
	//Single character tokens
	LEFT_PAREN,RIGHT_PAREN,LEFT_BRACE,RIGHT_BRACE,
	COMMA,DOT,MINUS,PLUS,SEMICOLON,SLASH,STAR,
	
	//One or two character tokens
	BANG,BANG_EQUAL,
	EQUAL,EQUAL_EQUAL,
	GREATER,GREATER_EQUAL,
	LESS,LESS_EQUAL,

	//Literals
	IDENTIFIER,STRING,NUMBER,
	
	//Keywords
	AND,CLASS,ELSE,FALSE,FUN,FOR,IF,NIL,OR,
	PRINT,RETURN,SUPER,THIS,TRUE,VAR,WHILE,

	T_EOF,
	
};

//The class used to store a token
class Token{
	private:
		TokenType type;
		std::string lexeme="";
		double value;
		int line;
	public:
		Token(TokenType type,std::string lexeme,int line);
		Token(TokenType type,double value,int line);
		//Overload the extraction operator
		void print();
		

};


#endif
