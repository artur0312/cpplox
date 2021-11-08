INC= -I ./include
CPPSRC=src/*.cpp
FLAGS=-fmax-errors=5

main:
	g++ $(INC) $(CPPSRC) -o cpplox 

astTree:
	g++ $(INC) $(FLAGS) ./src/token.cpp ./src/printer/AstPrinter.cpp -o printtree
