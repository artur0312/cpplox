//The header defining the classes for the astTree
#ifndef AST_TREE_H
#define AST_TREE_H
#include "token.h"

//Forward declaration of the classes
class Binary;
class Grouping;
class Literal;
class Unary;

class Visitor{
	public:
		virtual std::string visitBinary(Binary)=0;
		virtual std::string visitGrouping(Grouping)=0;
		virtual std::string visitLiteral(Literal)=0;
		virtual std::string visitUnary(Unary)=0;
};

class Expr{
	//A virtual function to allow the instantiation of Expr
	public:
		virtual std::string accept(Visitor &v)=0;
};


class Grouping: public Expr{
	public:
		Grouping(Expr *expression): expression(expression){
		}
		std::string accept(Visitor &v) {
			std::cout<<"Grouping\n";
			return v.visitGrouping(*this);
		}
		const Expr *expression;
};

class Literal:public Expr{
	public:
		Literal(Token value):value(value){
		}
		std::string accept(Visitor &v) {
			std::cout<<"Literal\n";
			return v.visitLiteral(*this);
		}
		const Token value;
};

class Binary:public Expr{
	public:
		Binary(Expr *left,Token op, Expr * right):left(left),op(op),right(right){
		}

		std::string accept(Visitor &v) {
			std::cout<<"Binary\n";
			return v.visitBinary(*this);
		}

		const Expr *left;
		const Token op;
		const Expr *right;
};

class Unary: public Expr{
	public:
		Unary(Token op, Expr *right):op(op),right(right){
		}
		std::string accept(Visitor &v) {
			std::cout<<"Unary\n";
			return v.visitUnary(*this);
		}
		const Token op;
		const Expr *right;
};

#endif
