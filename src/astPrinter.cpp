//Implements an AST printer
#include "astPrinter.h"

std::string AstPrinter::print(Expr<std::string> &expr){
	return expr.accept(*this);
}

//Parameters: number of parameters passed, excluding the int, but including the string
std::string AstPrinter::parenthesize(int parameters,std::string name,...){
	va_list args;
	va_start(args,name);
	std::string s="("+name;
	Expr<std::string> *expr;
	for(int i=0;i<parameters-1;i++){
		expr=va_arg(args,Expr<std::string> *);
		s+=" "+expr->accept(*this);
	}
	s+=")";
	va_end(args);
	return s;
}



