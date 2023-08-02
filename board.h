#include <SFML/Graphics.hpp>
#include <vector>
#include "tiles.h"

using namespace std;

class Board {
public:    
    Board(sf::RenderWindow& window, int numMines, float numTiles, int numCol, int numRow);
    void drawBoard();
    int getNumFlags();
    void setFlag(int tileNumber);
    void setReveal(int tileNumber);
    void setAdjacent();
    void debug(sf::RenderWindow& window);
    bool checkOver();
    bool checkWin();
    void recursion(int tileNumber);

private:
    sf::RenderWindow& window;
    vector<Tile> tiles;
    int numCol;
    int numRow;
    bool gameOver = false;
};

//Neighbors Display
//
//    0  1  2
//    7  i  3
//    6  5  4