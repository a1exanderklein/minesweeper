#include "tiles.h"

Tile::Tile(sf::Vector2f position, TextureManager& txm) : position(position),
    hiddenTx(txm.getTx("hiddenTx")),
    revealedTx(txm.getTx("revealedTx")),
    flagTx(txm.getTx("flagTx")),
    mineTx(txm.getTx("mineTx")),
    oneTx(txm.getTx("oneTx")),
    twoTx(txm.getTx("twoTx")),
    threeTx(txm.getTx("threeTx")),
    fourTx(txm.getTx("fourTx")),
    fiveTx(txm.getTx("fiveTx")),
    sixTx(txm.getTx("sixTx")),
    sevenTx(txm.getTx("sevenTx")),
    eightTx(txm.getTx("eightTx")) {
    state = HIDDEN;
    for (int i = 0; i < 8; i++) {
        adjacent[i] = nullptr;
    }
    // hiddenTx.loadFromFile("files/images/tile_hidden.png");
    // revealedTx.loadFromFile("files/images/tile_revealed.png");
    // flagTx.loadFromFile("files/images/flag.png");
    // mineTx.loadFromFile("files/images/mine.png");    
    // oneTx.loadFromFile("files/images/number_1.png");
    // twoTx.loadFromFile("files/images/number_2.png");
    // threeTx.loadFromFile("files/images/number_3.png");
    // fourTx.loadFromFile("files/images/number_4.png");
    // fiveTx.loadFromFile("files/images/number_5.png");
    // sixTx.loadFromFile("files/images/number_6.png");
    // sevenTx.loadFromFile("files/images/number_7.png");
    // eightTx.loadFromFile("files/images/number_8.png");
};

State Tile::getState() {
    return state;
}

void Tile::setState(State newState) {
    state = newState;
}

void Tile::drawNums(sf::RenderWindow& window) {
    if (state == REVEALED && minesTouching == 1 && mine == false) {
        sf::Sprite oneSprite(oneTx);
        oneSprite.setPosition(position);
        window.draw(oneSprite);
    }
    if (state == REVEALED && minesTouching == 2 && mine == false) {
        sf::Sprite twoSprite(twoTx);
        twoSprite.setPosition(position);
        window.draw(twoSprite);
    }
    if (state == REVEALED && minesTouching == 3 && mine == false) {
        sf::Sprite threeSprite(threeTx);
        threeSprite.setPosition(position);
        window.draw(threeSprite);
    }
    if (state == REVEALED && minesTouching == 4 && mine == false) {
        sf::Sprite fourSprite(fourTx);
        fourSprite.setPosition(position);
        window.draw(fourSprite);
    }
    if (state == REVEALED && minesTouching == 5 && mine == false) {
        sf::Sprite fiveSprite(fiveTx);
        fiveSprite.setPosition(position);
        window.draw(fiveSprite);
    }
    if (state == REVEALED && minesTouching == 6 && mine == false) {
        sf::Sprite sixSprite(sixTx);
        sixSprite.setPosition(position);
        window.draw(sixSprite);
    }
    if (state == REVEALED && minesTouching == 7 && mine == false) {
        sf::Sprite sevenSprite(sevenTx);
        sevenSprite.setPosition(position);
        window.draw(sevenSprite);
    }
    if (state == REVEALED && minesTouching == 8 && mine == false) {
        sf::Sprite eightSprite(eightTx);
        eightSprite.setPosition(position);
        window.draw(eightSprite);
    }
}

void Tile::drawState(sf::RenderWindow& window, bool paused, bool debugging, bool gameLost) {
    if (paused == false && debugging == false) { //default
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
        if (state == REVEALED && mine == true) {
            sf::Sprite mineSprite(mineTx);
            mineSprite.setPosition(position);
            window.draw(mineSprite);
        }
        drawNums(window);
    }
    if (paused == true) { //paused mode
        spriteTile.setTexture(revealedTx);
        spriteTile.setPosition(position);
        window.draw(spriteTile);
    }
    if (debugging == true && paused == false) { //debugging mode
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
        if (state == HIDDEN && mine == true) {
            sf::Sprite mineSprite(mineTx);
            mineSprite.setPosition(position);
            window.draw(mineSprite);
        }
        if (state == REVEALED && mine == true) {
            sf::Sprite mineSprite(mineTx);
            mineSprite.setPosition(position);
            window.draw(mineSprite);
        }
        drawNums(window);
    }
    if (gameLost == true) {
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
        if (state == REVEALED && mine == true) {
            sf::Sprite mineSprite(mineTx);
            mineSprite.setPosition(position);
            window.draw(mineSprite);
        }
        if (state == HIDDEN && mine == true) {
            setState(REVEALED);
            sf::Sprite mineSprite(mineTx);
            mineSprite.setPosition(position);
            window.draw(mineSprite);
        }
        if (state == FLAGGED && mine == true) {
            sf::Sprite mineSprite(mineTx);
            mineSprite.setPosition(position);
            window.draw(mineSprite);
        }
        drawNums(window);
        
    }
}

void Tile::setMine() {
    mine = true;
}

bool Tile::getMine() {
    if (mine == true) {
        return true;
    }
    else {
        return false;
    }
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

void Tile::addAdjacent(Tile* adjacentTile, int location) {
    adjacent[location] = adjacentTile;
}

void Tile::setTouching(int num) {
    minesTouching = num;
}