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

void Board::setFlag(int tileNumber) {
    tiles[tileNumber].flag();
}