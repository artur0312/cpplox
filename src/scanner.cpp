#include "scanner.h"
#include "errors.h"

//File that contains the functions used to parse a string into tokens
Scanner::Scanner(std::string str_source){
	source.str(str_source);
}

std::vector<Token> Scanner::scanTokens(){
	//While there are more characters
	while(source.tellg()<source.str().length()){
		//Search for the next token
		scanNextToken();
	}
	tokens.push_back(Token(T_EOF,"EOF",line));
	return tokens;
}

void Scanner::scanNextToken(){
	//get the next character
	char c=source.get();
	switch(c){
		//One character tokens
		case '(':
			addToken(LEFT_PAREN,"(");
			break;
		case ')':
			addToken(RIGHT_PAREN,")");
			break;
		case '{':
			addToken(LEFT_BRACE,"{");
			break;
		case '}':
			addToken(RIGHT_BRACE,"}");
			break;
		case ',':
			addToken(COMMA,",");
			break;
		case '.':
			addToken(DOT,".");
			break;
		case '-':
			addToken(MINUS,"-");
			break;
		case '+':
			addToken(PLUS,"+");
			break;
		case ';':
			addToken(SEMICOLON,";");
			break;
		case '*':
			addToken(STAR,"*");
			break;
			//One or two character lexemes
		case '!':
			if(match('=')){
				addToken(BANG_EQUAL,"!=");
			}
			else{
				addToken(BANG,"!");
			}
			break;
		case '=':
			if(match('=')){
				addToken(EQUAL_EQUAL,"==");
			}
			else{
				addToken(EQUAL,"=");
			}
			break;
		case '<':
			if(match('=')){
				addToken(LESS_EQUAL,"<=");
			}
			else{
				addToken(LESS,"<");
			}
			break;
		case '>':
			if(match('=')){
				addToken(GREATER_EQUAL,">=");
			}
			else{
				addToken(GREATER,">");
			}
			break;
			//Handles the '/' character, which can indicate the start of a comment
		case '/':
			if(match('/')){
				while(source.peek()!='\n' && !source.eof())
					source.get();
			}
			//Multiline comment
			else if(match('*')){
				while(!source.eof() && (source.peek()!='*' || peekNext()!='/')){
					c=source.get();
					if(c=='\n'){
						line ++;
					}
				}
				//The '*' and '/' characters
				source.get();
				source.get();
				}
			else{
				addToken(SLASH,"/");
			}
			break;
			//Handles whitespaces
		case ' ':
		case '\r':
		case '\t':
			break;
		case '\n':
			line++;
			break;
			//Create strings
		case '"':
			string();
			break;
			//If we dont recognize the character
		default:
			//verify if is a number
			if(isdigit(c)){
				//Read again c
				source.putback(c);
				number();
			}
			//verify if is an identifier
			else if(std::isalpha(c) || c=='_'){
				source.putback(c);
				identifier();
			}
			else{
				error(line,"Unexpected character.\n");
				break;
			}
	}
}

void Scanner::addToken(TokenType t){
	tokens.push_back(Token(t,"",line));
}
void Scanner::addToken(TokenType t,std::string s){
	tokens.push_back(Token(t,s,line));
}
void Scanner::addToken(TokenType t,double d){
	tokens.push_back(Token(t,d,line));
}

//See if the next character on source matches c. If it does, reads the character
bool Scanner::match(char c){
	char next=source.peek();
	if(next!=c){
		return false;
	}
	//If matches, read the character
	source.get();
	return true;
}
//Create a string token after reading a '"'
void Scanner::string(){
	std::string s;
	while(source.peek()!='"' && !source.eof()){
		if(source.peek()=='\n')
			line++;
		s+=source.get();
	}
	if(source.eof()){
		error(line,"Unterminated string");
		return;
	}

	//The closing "
	source.get();
	addToken(STRING,s);
}

//Create a token for number literals and adds to tokens
//It doesnt support a leading decimal point
void Scanner::number(){
	std::string s;
	while(isdigit(source.peek()))
		s+=source.get();
	//look for a decimal part
	if(source.peek()=='.' and  std::isdigit(peekNext())){
		//Consumes the point
		s+=source.get();
		while(std::isdigit(source.peek())){
			s+=source.get();
		}
	}
	addToken(NUMBER,std::stod(s));

}
//Create a token for identifiers and add to tokens
void Scanner::identifier(){
	std::string s;
	while(isalnum(source.peek()) or source.peek()=='_'){
		s+=source.get();
	}
	if(keywords.find(s)==keywords.end()){
		addToken(IDENTIFIER,s);
	}
	else{
		addToken(keywords.at(s),s);
	}
}





//Returns the character two positions ahead of source
char Scanner::peekNext(){
	if((int)source.tellg()+1>=source.str().length())
		return '\0';
	return source.str()[(int)source.tellg()+1];
}


