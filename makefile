all: derle bagla calistir

derle:
	g++ -c -I "./include" ./src/main.cpp -o ./lib/main.o
	g++ -c -I "./include" ./src/Shape.cpp -o ./lib/Shape.o

bagla:
	g++ ./lib/main.o ./lib/Shape.o -o ./bin/program.exe

calistir:
	./bin/program.exe