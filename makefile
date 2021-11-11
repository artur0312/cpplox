INC= -I ./include
CPPSRC=src/*.cpp
FLAGS=-fmax-errors=5

scanner:
	g++ $(INC) $(CPPSRC) -o cpplox 

astTree:
	g++ $(INC) $(FLAGS) ./src/token.cpp ./src/printer/astPrinter.cpp -o printTree
