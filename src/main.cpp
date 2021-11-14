#include "errors.h"
#include "token.h"
#include "scanner.h"
#include "parser.h"
#include "astTree.h"
#include "astPrinter.h"
#include "main.h"
//Keeps track if there is an error during the execution
bool hadError=false;

int main(int argc,char *argv[]){
	//Incorrect number of arguments
	if(argc>2){
		std::cout<<"Usage: cpplox [script]";
		exit(64);
	}
	//Pass the path for a file
	else if(argc==2){
		runFile(argv[1]);
	}
	//Run interactively
	else{
		runPrompt();
	}
}

//Function to run from a file
void runFile(std::string path){
	//Read the file and store it in a stringstream
	std::ifstream input_file(path);
	std::stringstream buffer;
	buffer<<input_file.rdbuf();
	//Pass the string as an argument
	run(buffer.str());
	//indicates that the program ended with an error
	if(hadError)
		exit(65);
}

//Function to run interactively
void runPrompt(){
	while(true){
		std::cout<<">";
		std::string line;
		std::getline(std::cin,line);
		//Enter exit to quit the program
		if(line=="exit"){
			break;
		}
		run(line);
		//reset the error flag if there was one on the execution of the line
		if(hadError){
			hadError=false;
		}
	}
}

void run(std::string source){
	//Get the tokens
	Scanner scan(source);
	std::vector<Token> tokens=scan.scanTokens();

	Parser parse(tokens);
	Expr<std::string> *expression=parse.parse();
	
	//Stop if there was a syntax error
	if(hadError)
		return;

	AstPrinter printer;
	std::cout<<printer.print(*expression)<<'\n';
}
	
	
	

	
