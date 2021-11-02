#ifndef ERRORS_H
#define ERRORS_H
#include <string>
#include<iostream>
//This variable keeps track if there was an error
extern bool hadError;

//prints an error message indicating in which line there is a problem
void error(int line,std::string message);

//Prints an error message and says where in the line there is a problem
void report(int line,std::string where, std::string message);
#endif
