#include <SFML/Graphics.hpp>
#include <vector>
#include "tiles.h"

using namespace std;

class Board {
public:    
    Board(sf::RenderWindow& window, float numTiles, float numCol, float numRow);
    void drawBoard();
    int getNumFlags();
    void setFlag(int tileNumber);
    void setReveal(int tileNumber);

private:
    sf::RenderWindow& window;
    vector<Tile> tiles;
    float numCol;
    float numRow;
};