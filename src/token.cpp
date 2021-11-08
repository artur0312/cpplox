//This file implements the interface to handle tokens
#include "token.h"
#include "errors.h"

//Build a literal, like a string
Token::Token(TokenType i_type,std::string i_lexeme,int i_line){
	type=i_type;
	lexeme=i_lexeme;
	line=i_line;
}

//Build a number
Token::Token(TokenType i_type,double i_value,int i_line){
	type=i_type;
	value=i_value;
	line=i_line;
}
//Print the token
void Token::print(){
	if(lexeme!="")
		std::cout<<type<<" "<<lexeme<<" "<<'\n';
	else
		std::cout<<type<<" "<<value<<" "<<'\n';

}

//Getter methods
TokenType Token::getType() const{
	return type;
}

std::string Token::getLexeme() const{
	return lexeme;
}

double Token::getValue() const{
	return value;
}

int Token::getLine() const{
	return line;
}
