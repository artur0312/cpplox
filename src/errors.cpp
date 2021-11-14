#include "errors.h"
//Here are the functions associated with the error messages of the language


//prints an error message indicating in which line there is a problem
void error(int line,std::string message){
	report(line,"",message);
}

//Prints an error message and says where in the line there is a problem
void report(int line,std::string where, std::string message){
	std::cerr<<"[line "<<line<<"] Error"<<where<<": "<<message<<'\n';
	hadError=true;
}

//Parse error constructor
ParseError::ParseError(){
}


ParseError error(Token token,std::string message){
	error_message(token,message);
	return ParseError();
}

void error_message(Token token,std::string message){
	if(token.getType()==EOF){
		report(token.getLine()," at end", message);
	}
	else if (token.getLexeme()!=""){
		report(token.getLine()," at '"+token.getLexeme()+"'",message);
	}
	else{
		report(token.getLine()," at '"+std::to_string(token.getValue())+"'",message);
	}
}

