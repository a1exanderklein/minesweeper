#include "board.h"

Board::Board(sf::RenderWindow& window, TextureManager& txm, int numMines, float numTiles, int numCol, int numRow) : window(window){
    this -> numCol = numCol;
    this -> numRow = numRow;
    this -> numMines = numMines;
    this -> numTiles = numTiles;

    float size = 32.0f;
    for (int i = 0; i < numRow; i++) {
        for (int j = 0; j < numCol; j++) {
            Tile tile(sf::Vector2f(j * size, i * size), txm);
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
void Board::reset(TextureManager& txm) {
    tiles.clear();
    float size = 32.0f;
    for (int i = 0; i < numRow; i++) {
        for (int j = 0; j < numCol; j++) {
            Tile tile(sf::Vector2f(j * size, i * size), txm);
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
    gameOver = false;
}

void Board::drawBoard(bool paused, bool debugging, bool gameLost) {
    for (int i = 0; i < tiles.size(); i++) {
        tiles[i].drawState(window, paused, debugging, gameLost);
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

void Board::setWinFlag() {
    for (int i = 0; i < tiles.size(); i++) {
        if (tiles[i].getMine() == true) {
            if (tiles[i].getState() == HIDDEN) {
                tiles[i].flag();
            }
        }
    }    
}

void Board::setReveal(int tileNumber) {
    if (tiles[tileNumber].minesTouching == 0) {
        recursion(tileNumber);
    }
    tiles[tileNumber].reveal();
    if (tiles[tileNumber].getMine() == true) {
        gameOver = true;
    }
}

void Board::recursion(int tileNumber) {
    Tile* current = &tiles[tileNumber];
    if (current->getState() == REVEALED) {
        return;
    }
    current->reveal();
    if (current->minesTouching == 0 && current->getMine() == false) {
        for (int i = 0; i < 8; i++) {
            if (current->adjacent[i] != nullptr) {
                //index of tile given by pointer subtraction
                int adjacentIndex = current->adjacent[i] - &tiles[0];
                //ensures its within board range
                if (adjacentIndex >= 0 && adjacentIndex < tiles.size()) {
                    recursion(adjacentIndex);
                }
            }
        }
    }
}

bool Board::checkOver() {
    return gameOver;
}

bool Board::checkWin() {
    int safeTiles = 0;
    for (int i = 0; i < tiles.size(); i++) {
        if (tiles[i].getState() == HIDDEN && tiles[i].getMine() == false) {
            safeTiles++;
        }
        if (tiles[i].getState() == FLAGGED && tiles[i].getMine() == false) {
            safeTiles++;
        }
    }
    if (safeTiles > 0) {
        return false;
    } else {
        gameOver = true;
        return true;
    }

}

void Board::setAdjacent() {
    for (int i = 0; i < tiles.size(); i++) {
        int x = i % numCol;
        int y = i / numCol;
        
        // Corners
        if (x == 0 && y == 0) { //Top Left
            tiles[i].addAdjacent(&tiles[i + 1], 3);
            tiles[i].addAdjacent(&tiles[i + numCol + 1], 4);
            tiles[i].addAdjacent(&tiles[numCol], 5);
            continue;
        }
        if (x == numCol - 1 && y == 0) { //Top Right
            tiles[i].addAdjacent(&tiles[i - 1], 7);
            tiles[i].addAdjacent(&tiles[i + numCol - 1], 6);
            tiles[i].addAdjacent(&tiles[i + numCol ], 5);
            continue;
        }
        if (x == 0 && y == numRow - 1) { //Bottom Left
            tiles[i].addAdjacent(&tiles[i - numCol], 1);
            tiles[i].addAdjacent(&tiles[i - numCol + 1], 2);
            tiles[i].addAdjacent(&tiles[i + 1], 3);
            continue;
        }
        if (x == numCol - 1 && y == numRow - 1) { //Bottom Right
            tiles[i].addAdjacent(&tiles[i - numCol], 1);
            tiles[i].addAdjacent(&tiles[i - numCol - 1], 0);
            tiles[i].addAdjacent(&tiles[i - 1], 7);
            continue;
        } 

        // Sides
        else if (y == 0) { // Top side
            tiles[i].addAdjacent(&tiles[i - 1], 7);
            tiles[i].addAdjacent(&tiles[i + numCol - 1], 6);
            tiles[i].addAdjacent(&tiles[i + numCol], 5);
            tiles[i].addAdjacent(&tiles[i + numCol + 1], 4);
            tiles[i].addAdjacent(&tiles[i + 1], 3);
        }
        else if (y == numRow - 1) { // Bottom side
            tiles[i].addAdjacent(&tiles[i - 1], 7);
            tiles[i].addAdjacent(&tiles[i - numCol - 1], 0);
            tiles[i].addAdjacent(&tiles[i - numCol], 1);
            tiles[i].addAdjacent(&tiles[i - numCol + 1], 2);
            tiles[i].addAdjacent(&tiles[i + 1], 3);
        }
        else if (x == 0) { // Left side
            tiles[i].addAdjacent(&tiles[i - numCol], 1);
            tiles[i].addAdjacent(&tiles[i - numCol + 1], 2);
            tiles[i].addAdjacent(&tiles[i + 1], 3);
            tiles[i].addAdjacent(&tiles[i + numCol + 1], 4);
            tiles[i].addAdjacent(&tiles[i + numCol], 5);
        }
        else if (x == numCol - 1) { // Right side
            tiles[i].addAdjacent(&tiles[i - numCol], 1);
            tiles[i].addAdjacent(&tiles[i - numCol - 1], 0);
            tiles[i].addAdjacent(&tiles[i - 1], 7);
            tiles[i].addAdjacent(&tiles[i + numCol - 1], 6);
            tiles[i].addAdjacent(&tiles[i + numCol], 5);
        }

        // Remaining
        else {
            tiles[i].addAdjacent(&tiles[i - numCol - 1], 0);
            tiles[i].addAdjacent(&tiles[i - numCol], 1);
            tiles[i].addAdjacent(&tiles[i - numCol + 1], 2);
            tiles[i].addAdjacent(&tiles[i + 1], 3);
            tiles[i].addAdjacent(&tiles[i + numCol + 1], 4);
            tiles[i].addAdjacent(&tiles[i + numCol], 5);
            tiles[i].addAdjacent(&tiles[i + numCol - 1], 6);
            tiles[i].addAdjacent(&tiles[i - 1], 7);
        }
    }
}

