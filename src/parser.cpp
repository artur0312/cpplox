#include "parser.h"

Parser::Parser(std::vector<Token> token){
	this->tokens=token;
}

//Code each rule as a function
Expr<std::string> *Parser::expression(){
	return equality();
}

Expr<std::string> *Parser::equality(){
	Expr<std::string> *expr=comparison();

	while(match(2,BANG_EQUAL,EQUAL_EQUAL)){
		Token op=previous();
		Expr<std::string> *right=comparison();
		expr = new Binary<std::string>(expr,op,right);
	}

	return expr;
}

Expr<std::string> *Parser::comparison(){
	Expr<std::string> *expr=term();

	while(match(4,GREATER,GREATER_EQUAL,LESS,LESS_EQUAL)){
		Token op=previous();
		Expr<std::string> *right=term();
		expr=new Binary<std::string>(expr,op,right);
	}
	return expr;
}

Expr<std::string> *Parser::term(){
	Expr<std::string> *expr=factor();

	while(match(2,PLUS,MINUS)){
		Token op=previous();
		Expr<std::string>* right=factor();
		expr=new Binary<std::string>(expr,op,right);
	}

	return expr;
}

Expr<std::string> *Parser::factor(){
	Expr<std::string> *expr=unary();

	while(match(2,SLASH,STAR)){
		Token op=previous();
		Expr<std::string>* right=unary();
		expr=new Binary<std::string>(expr,op,right);
	}

	return expr;
}	

Expr<std::string> *Parser::unary(){
	if(match(2,BANG,MINUS)){
		Token op=previous();
		Expr<std::string>* right=unary();
		return new Unary<std::string>(op,right);
	}
	return primary();
}

Expr<std::string> *Parser::primary(){
	if(match(5,FALSE,TRUE,NIL,NUMBER,STRING)){
		return new Literal<std::string>(previous());
	}
	else if(match(1,LEFT_PAREN)){
		Expr<std::string>* expr=expression();
		consume(RIGHT_PAREN,"Expect ')' after expression.");
		return new Grouping<std::string>(expr);
	}
	throw error(peek(),"Expect expression");
}




//Helper functions
bool Parser::match(int count,...){
	va_list args;
	va_start(args,count);
	for(int i=0;i<count;i++){
		int type=va_arg(args,int);
		if(check((TokenType)type)){
			advance();
			return true;
		}
	}
	return false;
}

bool Parser::check(TokenType type){
	if(isAtEnd()){
		return false;
	}
	return peek().getType()==type;
}

Token Parser::advance(){
	if(!isAtEnd()){
		current++;
	}
	return previous();
}

bool Parser::isAtEnd(){
	return peek().getType()==EOF;
}

Token Parser::peek(){
	return tokens[current];
}

Token Parser::previous(){
	return tokens[current-1];
}

//Error handling
Token Parser::consume(TokenType type,std::string message){
	if(check(type)){
		return advance();
	}
	throw error(peek(),message);
}

//This function consume tokens until reaching the end of an statement
void Parser::synchronize(){
	advance();
	while(!isAtEnd()){
		if(previous().getType()==SEMICOLON) return;
		switch(peek().getType()){
			case CLASS:
			case FUN:
			case VAR:
			case FOR:
			case WHILE:
			case IF:
			case PRINT:
			case RETURN:
				return;
		}

		advance();
	}
}

Expr<std::string> *Parser::parse(){
	try{
		return expression();
	}catch (ParseError error){
		return nullptr;
	}
}


