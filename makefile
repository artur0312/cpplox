INC= -I ./include
CPPSRC=src/*.cpp

main:
	g++ $(INC) $(CPPSRC) -o cpplox 
