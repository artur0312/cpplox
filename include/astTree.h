//The header defining the classes for the astTree
#ifndef AST_TREE_H
#define AST_TREE_H
#include "token.h"

//Forward declaration of the classes
template <class T> class Binary;
template <class T> class Grouping;
template <class T> class Literal;
template <class T> class Unary;

template <class T>
class Visitor{
	public:
		virtual T visitBinary(Binary<T>)=0;
		virtual T visitGrouping(Grouping<T>)=0;
		virtual T visitLiteral(Literal<T>)=0;
		virtual T visitUnary(Unary<T>)=0;
};

template <class T>
class Expr{
	//A virtual function to allow the instantiation of Expr
	public:
		virtual T accept(Visitor<T> &v)=0;
};


template <class T>
class Grouping: public Expr<T>{
	public:
		Grouping(Expr<T> *expression): expression(expression){
		}
		T accept(Visitor<T> &v) {
			return v.visitGrouping(*this);
		}
		const Expr<T> *expression;
};

template <class T>
class Literal:public Expr<T>{
	public:
		Literal(Token value):value(value){
		}
		T accept(Visitor<T> &v) {
			return v.visitLiteral(*this);
		}
		const Token value;
};

template <class T>
class Binary:public Expr<T>{
	public:
		Binary(Expr<T> *left,Token op, Expr<T> * right):left(left),op(op),right(right){
		}

		T accept(Visitor<T> &v) {
			return v.visitBinary(*this);
		}

		const Expr<T> *left;
		const Token op;
		const Expr<T> *right;
};

template <class T>
class Unary: public Expr<T>{
	public:
		Unary(Token op, Expr<T> *right):op(op),right(right){
		}
		T accept(Visitor<T> &v) {
			return v.visitUnary(*this);
		}
		const Token op;
		const Expr<T> *right;
};

#endif
