#include <SFML/Graphics.hpp>
#include <vector>
#include "tiles.h"
#include "TextureManager.h"

using namespace std;

class Board {
public:    
    Board(sf::RenderWindow& window, TextureManager& txm, int numMines, float numTiles, int numCol, int numRow);
    void reset(TextureManager& txm);
    void drawBoard(bool paused, bool debugging, bool gameLost);
    int getNumFlags();
    void setFlag(int tileNumber);
    void setWinFlag();
    void setReveal(int tileNumber);
    void setAdjacent();
    bool checkOver();
    bool checkWin();
    void recursion(int tileNumber);

private:
    sf::RenderWindow& window;
    vector<Tile> tiles;
    int numCol;
    int numRow;
    int numMines;
    float numTiles;
    bool gameOver = false;
};

//Neighbors Display
//
//    0  1  2
//    7  i  3
//    6  5  4