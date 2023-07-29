default:
	g++ -c main.cpp WelcomeWindow.cpp -IC:\SFML-2.6.0\include
	g++ main.o WelcomeWindow.o -o main -LC:\SFML-2.6.0\lib -lsfml-graphics -lsfml-window -lsfml-system
	.\main.exe