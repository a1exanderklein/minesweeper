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
    State getState();
    void drawState(sf::RenderWindow& window);
    void setMine();
    bool getMine();
    void debugMine(sf::RenderWindow& window);
    void flag();
    void reveal();
    void addAdjacent(Tile* adjacent, int location);
    void setTouching(int num);
    
    Tile* adjacent[8];
    int minesTouching = 0;

    sf::Texture hiddenTx;
    sf::Texture revealedTx;
    sf::Texture flagTx;
    sf::Texture mineTx;
    sf::Texture oneTx;
    sf::Texture twoTx;
    sf::Texture threeTx;
    sf::Texture fourTx;
    sf::Texture fiveTx;
    sf::Texture sixTx;
    sf::Texture sevenTx;
    sf::Texture eightTx;

private:
    State state;
    sf::Sprite spriteTile;
    sf::Vector2f position;
    bool mine = false;
};