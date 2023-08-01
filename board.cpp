#include "board.h"

Board::Board(sf::RenderWindow& window, int numMines, float numTiles, int numCol, int numRow) : window(window){
    this -> numCol = numCol;
    this -> numRow = numRow;

    float size = 32.0f;
    for (int i = 0; i < numCol; i++) {
        for (int j = 0; j < numRow; j++) {
            Tile tile(sf::Vector2f(i * size, j * size));
            tiles.push_back(tile);
        }
    }
    int numPlaced = 0;
    while (numPlaced < numMines) {
        int random = rand() % static_cast<int>(numTiles);
        if (tiles[random].getMine() == false) {
            tiles[random].setMine();
            numPlaced++;
        }
    }
    setAdjacent();
    for (int i = 0; i < tiles.size(); i++) {
        int number = 0;
        for (int j = 0; j < 8; j++) {
            if (tiles[i].adjacent[j] != nullptr) {
                if (tiles[i].adjacent[j]->getMine() == true) {
                    number++;
                }
            }
        }
        tiles[i].setTouching(number);
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

void Board::setAdjacent() {
    for (int i = 0; i < tiles.size(); i++) {
        int x = i / numRow;
        int y = i % numRow;   
        //Corners
        if (x == 0 && y == 0) { //Top Left
            tiles[i].addAdjacent(&tiles[numRow], 3);
            tiles[i].addAdjacent(&tiles[i + numRow], 4);
            tiles[i].addAdjacent(&tiles[i + 1], 5);
        }
        if (x == numCol - 1 && y == 0) { //Top Right
            tiles[i].addAdjacent(&tiles[i - numRow], 7);
            tiles[i].addAdjacent(&tiles[i - numRow + 1], 6);
            tiles[i].addAdjacent(&tiles[i + 1], 5);
        }
        if (x == 0 && y == numRow - 1) { //Bottom Left
            tiles[i].addAdjacent(&tiles[i - 1], 1);
            tiles[i].addAdjacent(&tiles[i * 2], 2);
            tiles[i].addAdjacent(&tiles[(i * 2) + 1], 3);
        }
        if (x == numCol - 1 && y == numRow - 1) { //Bottom Right
            tiles[i].addAdjacent(&tiles[i - 1], 1);
            tiles[i].addAdjacent(&tiles[i - numRow - 1], 0);
            tiles[i].addAdjacent(&tiles[i - numRow], 7);
        } 

        //Sides
        else if (y == 0) { // Top side
            tiles[i].addAdjacent(&tiles[i - numRow], 7);
            tiles[i].addAdjacent(&tiles[i - numRow + 1], 6);
            tiles[i].addAdjacent(&tiles[i + 1], 5);
            tiles[i].addAdjacent(&tiles[i + numRow + 1], 4);
            tiles[i].addAdjacent(&tiles[i + numRow], 3);
        }
        else if (y == numRow - 1) { // Bottom side
            tiles[i].addAdjacent(&tiles[i - numRow], 7);
            tiles[i].addAdjacent(&tiles[i - numRow - 1], 0);
            tiles[i].addAdjacent(&tiles[i - 1], 1);
            tiles[i].addAdjacent(&tiles[i + numRow - 1], 2);
            tiles[i].addAdjacent(&tiles[i + numRow], 3);
        }
        else if (x == 0) { // Left side
            tiles[i].addAdjacent(&tiles[i - 1], 1);
            tiles[i].addAdjacent(&tiles[i + numRow - 1], 2);
            tiles[i].addAdjacent(&tiles[i + numRow], 3);
            tiles[i].addAdjacent(&tiles[i + numRow + 1], 4);
            tiles[i].addAdjacent(&tiles[i + 1], 5);
        }
        else if (x == numCol - 1) { // Right side
            tiles[i].addAdjacent(&tiles[i - 1], 1);
            tiles[i].addAdjacent(&tiles[i - numRow - 1], 0);
            tiles[i].addAdjacent(&tiles[i - numRow], 7);
            tiles[i].addAdjacent(&tiles[i - numRow + 1], 6);
            tiles[i].addAdjacent(&tiles[i + 1], 5);
        }

        //Remaining
        else {
            tiles[i].addAdjacent(&tiles[i - numRow - 1], 0);
            tiles[i].addAdjacent(&tiles[i - 1], 1);
            tiles[i].addAdjacent(&tiles[i + numRow - 1], 2);
            tiles[i].addAdjacent(&tiles[i + numRow], 3);
            tiles[i].addAdjacent(&tiles[i + numRow + 1], 4);
            tiles[i].addAdjacent(&tiles[i + 1], 5);
            tiles[i].addAdjacent(&tiles[i - numRow + 1], 6);
            tiles[i].addAdjacent(&tiles[i - numRow], 7);
        }
    }
}