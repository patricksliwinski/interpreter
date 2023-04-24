FLAGS := -std=c++17
CC := g++
OBJECTS = main.o lox-interpreter.o scanner.o

main : $(OBJECTS)

main.o : src/main.cpp lox-interpreter.o scanner.o
	$(CC) -c src/main.cpp

lox-interpreter.o : src/lox-interpreter.cpp src/lox-interpreter.h
	$(CC) -c src/lox-interpreter.cpp

scanner.o : src/scanner.cpp src/scanner.h
	$(CC) -c src/scanner.cpp


clean:
	rm $(OBJECTS)
