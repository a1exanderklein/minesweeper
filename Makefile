default:
	g++ -c main.cpp WelcomeWindow.cpp board.cpp tiles.cpp -IC:\SFML-2.6.0\include
	g++ main.o WelcomeWindow.o board.o tiles.o -o main -LC:\SFML-2.6.0\lib -lsfml-graphics -lsfml-window -lsfml-system
	.\main.exe