#include "tiles.h"

Tile::Tile(sf::Vector2f position) : position(position) {
    state = HIDDEN;
};

void Tile::drawState(sf::RenderWindow& window) {
    sf::Texture hiddenTx;
    hiddenTx.loadFromFile("files/images/tile_hidden.png");
    sf::Texture revealedTx;
    revealedTx.loadFromFile("files/images/tile_revealed.png");
    sf::Texture flagTx;
    flagTx.loadFromFile("files/images/flag.png");
    if (state == HIDDEN) {
        spriteTile.setTexture(hiddenTx);
    }
    if (state == REVEALED) {
        spriteTile.setTexture(revealedTx);
    }
    spriteTile.setPosition(position);
    window.draw(spriteTile);

    if (state == FLAGGED) {
        sf::Sprite flagSprite(flagTx);
        flagSprite.setPosition(position);
        window.draw(flagSprite);
    }

}

State Tile::getState() {
    return state;
}


void Tile::flag() {
    if (state == HIDDEN) {
        state = FLAGGED;
    }
    else if (state == FLAGGED) {
        state = HIDDEN;
    }
}

void Tile::reveal() {
    if (state == HIDDEN) {
        state = REVEALED;
    }
}