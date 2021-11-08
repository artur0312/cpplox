//Implements an AST printer
//The expression still needs to be created manuall consty

#include<string>
#include<iostream>
#include<cstdarg>
#include "astTree.h"
#include "token.h"

class AstPrinter: public Visitor{
	public:
		std::string print(Expr &expr){
			return expr.accept(*this);
		}

		//Parameters: number of parameters passed, excluding the int, but including the string
		std::string parenthesize(int parameters,std::string name,...){
			va_list args;
			va_start(args,name);
			std::string s="("+name;
			Expr *expr;
			for(int i=0;i<parameters-1;i++){
				expr=va_arg(args,Expr *);
				s+=" "+expr->accept(*this);;
			}
			s+=")";
			va_end(args);
			return s;
		}


		//Implement the visit methods
		std::string visitBinary(Binary expr) {
			return parenthesize(3,expr.op.getLexeme(),expr.left,expr.right);
		}

		std::string visitGrouping(Grouping expr) {
			return parenthesize(2,"group",expr.expression);
		}
		std::string visitLiteral(Literal expr) {
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

		std::string visitUnary(Unary expr) {
			return parenthesize(2,expr.op.getLexeme(),expr.right);
		}
};

int main(){
	Expr *expr=new Binary(new Unary(Token(MINUS,"-",1),new Literal(Token(NUMBER,123,1))),
			Token(STAR,"*",1),
			new Grouping(new Literal(Token(NUMBER,45.67,1))));

	AstPrinter printer;
	std::cout<<printer.print(*expr)<<'\n';
}
