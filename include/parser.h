#ifndef PARSER_H
#define PARSER_H
#include<vector>
#include<iostream>
#include<cstdarg>
#include<string>
#include "errors.h"
#include "token.h"
#include "astTree.h"

class Parser{
	public:
		//Constructor
		Parser(std::vector<Token> token);

		//Function to start parsing
		Expr<std::string> *parse();
	private:
		std::vector<Token> tokens;
		int current=0;

		//Code each rule as a function
		Expr<std::string> *expression();
		Expr<std::string> *equality();
		Expr<std::string> *comparison();
		Expr<std::string> *term();
		Expr<std::string> *factor();
		Expr<std::string> *unary();
		Expr<std::string> *primary();

		//Helper functions
		bool match(int count,...);
		bool check(TokenType type);
		Token advance();
		bool isAtEnd();
		Token peek();
		Token previous();

		//Error handling
		Token consume(TokenType type, std::string msg);
		void synchronize();

};
#endif
