#ifndef AST_PRINTER_H
#define AST_PRINTER_H
#include<string>
#include<iostream>
#include<cstdarg>
#include "astTree.h"
#include "token.h"

class AstPrinter: public Visitor<std::string>{
	public:
		std::string print(Expr<std::string> &expr);

		//Parameters: number of parameters passed, excluding the int, but including the string
		std::string parenthesize(int parameters,std::string name,...);

//Implement the visit methods
//They need to be on the header because they depend of a template
std::string visitBinary(Binary<std::string> expr) {
	return parenthesize(3,expr.op.getLexeme(),expr.left,expr.right);
}

std::string visitGrouping(Grouping<std::string> expr) {
	return parenthesize(2,"group",expr.expression);
}
std::string visitLiteral(Literal<std::string> expr) {
	if(expr.value.getType()==STRING and expr.value.getLexeme()==""){
		return "nill";
	}
	else if(expr.value.getType()==STRING) {
		return expr.value.getLexeme();
	}	
	else{
		return std::to_string(expr.value.getValue());
	}
}

std::string visitUnary(Unary<std::string> expr) {
	return parenthesize(2,expr.op.getLexeme(),expr.right);
}
};

#endif
