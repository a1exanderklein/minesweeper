#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

enum State {
    HIDDEN,
    REVEALED,
    FLAGGED
};

class Tile {
public:
    Tile(sf::Vector2f position);
    void drawState(sf::RenderWindow& window);
    State getState();
    void flag();
    void reveal();
    
private:
    vector<Tile*> adjacent;
    State state;
    sf::Sprite spriteTile;
    sf::Vector2f position;
};