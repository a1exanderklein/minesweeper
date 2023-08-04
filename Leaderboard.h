#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <cctype>
#include <map>

using namespace std;

class Leaderboard {
public:
    Leaderboard(float width, float height);
    void operator()();
    bool exitProgram = false;
    map<string, string> leaders;
    void drawLeaders(sf::RenderWindow& window);
    void addWinner(string name, string time);

    float width;
    float height;
    sf::Font font;

private:
    void setText(sf::Text& text, float x, float y, bool center);
    void setCasing(std::string& name);
};