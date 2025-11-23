all: derle bagla calistir

derle:
	g++ -c -I "./include" ./src/main.cpp -o ./lib/main.o
	g++ -c -I "./include" ./src/Shape.cpp -o ./lib/Shape.o
	g++ -c -I "./include" ./src/Rectangle.cpp -o ./lib/Rectangle.o
	g++ -c -I "./include" ./src/Triangle.cpp -o ./lib/Triangle.o
	g++ -c -I "./include" ./src/Star.cpp -o ./lib/Star.o
	g++ -c -I "./include" ./src/FileHandler.cpp -o ./lib/FileHandler.o
	g++ -c -I "./include" ./src/ShapeNode.cpp -o ./lib/ShapeNode.o
	g++ -c -I "./include" ./src/ShapeList.cpp -o ./lib/ShapeList.o
	g++ -c -I "./include" ./src/MainNode.cpp -o ./lib/MainNode.o
	g++ -c -I "./include" ./src/DoubleList.cpp -o ./lib/DoubleList.o
	g++ -c -I "./include" ./src/Screen.cpp -o ./lib/Screen.o

bagla:
	g++ ./lib/main.o ./lib/Shape.o ./lib/Rectangle.o ./lib/Triangle.o ./lib/Star.o ./lib/FileHandler.o ./lib/ShapeNode.o ./lib/ShapeList.o ./lib/MainNode.o ./lib/DoubleList.o ./lib/Screen.o -o ./bin/program.exe

calistir:
	./bin/program.exe