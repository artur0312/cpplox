#include "errors.h"
//Here are the functions associated with the error messages of the language


//prints an error message indicating in which line there is a problem
void error(int line,std::string message){
	report(line,"",message);
}

//Prints an error message and says where in the line there is a problem
void report(int line,std::string where, std::string message){
	std::cerr<<"[line "<<line<<"] Error"<<where<<": "<<message;
	hadError=true;
}

