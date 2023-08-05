default:
	g++ -c *.cpp -IC:\SFML-2.6.0\include
	g++ *.o -o main -LC:\SFML-2.6.0\lib -lsfml-graphics -lsfml-window -lsfml-system
	.\main.exe