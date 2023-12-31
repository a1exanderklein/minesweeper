#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "TextureManager.h"

using namespace std;

enum State {
    HIDDEN,
    REVEALED,
    FLAGGED
};

class Tile {
public:
    Tile(sf::Vector2f position, TextureManager& txm);
    State getState();
    void setState(State newState);
    void drawState(sf::RenderWindow& window, bool paused, bool debugging, bool gameLost);
    void setMine();
    bool getMine();
    void flag();
    void reveal();
    void addAdjacent(Tile* adjacent, int location);
    void setTouching(int num);
    void drawNums(sf::RenderWindow& window);
    
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