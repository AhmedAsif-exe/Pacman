sfml-app: main.o
	g++ main.o -o sfml-app -lsfml-audio -lsfml-window -lsfml-graphics -lsfml-system

main.o: main.cpp
	g++ -c main.cpp
