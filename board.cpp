#include "board.h"

Board::Board(sf::RenderWindow& window, float numTiles, float numCol, float numRow) : window(window){
    float size = 32.0f;
    for (float i = 0; i < numCol; i++) {
        for (float j = 0; j < numRow; j++) {
            Tile tile(sf::Vector2f(i * size, j * size));
            tiles.push_back(tile);
        }
    }
}

void Board::drawBoard() {
    for (int i = 0; i < tiles.size(); i++) {
        tiles[i].drawState(window);
    }
}


int Board::getNumFlags() {
    int numFlags = 0;
    for (int i = 0; i < tiles.size(); i++) {
        if (tiles[i].getState() == FLAGGED) {
            numFlags++;
        }
    }
    return numFlags;
}

void Board::setFlag(int tileNumber) {
    tiles[tileNumber].flag();
}

void Board::setReveal(int tileNumber) {
    tiles[tileNumber].reveal();
}