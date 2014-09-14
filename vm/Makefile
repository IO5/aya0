.PHONY: clear all remake

CXX = g++

FLAGS = -std=c++11 -g -gdwarf-2 -O0 -DDEBUG
OBJ = function_prototype.o io_manager.o inst.o object_factory.o symbol_table.o test.o vm.o gc.o bind.o

all: test

test: $(OBJ)
	$(CXX) $(FLAGS) -o $@ $^  

bind.o: ../bind.cpp
	$(CXX) $(FLAGS) -o $@ -c $^

%.o: %.cpp
	$(CXX) $(FLAGS) -o $@ -c $^

remake: clear all

clear:
	rm -f *.o test
