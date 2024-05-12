sfml-app: main.o Game.o Dependencies.o
	g++ main.o -o sfml-app -lsfml-audio -lsfml-window -lsfml-graphics -lsfml-system

main.o: main.cpp Game.o Dependencies.o
	g++ -c main.cpp

Game.o: Game.cpp Dependencies.o Player.o
	g++ -c Game.cpp

Player.o: Dependencies.o
	g++ -c Player.h
Dependencies.o: Dependencies.h
	g++ -c Dependencies.h