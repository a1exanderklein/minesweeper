#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <cctype>

using namespace std;

class Welcome {
public:
    void operator()(float width, float height);
    bool exitProgram = false;
    string namePlayer;

private:
    void setText(sf::Text& text, float x, float y);
    void setCasing(std::string& name);
};