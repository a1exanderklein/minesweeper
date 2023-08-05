#include "TextureManager.h"

TextureManager::TextureManager() {
    sf::Texture happyFaceTx;
    happyFaceTx.loadFromFile("files/images/face_happy.png");
    textures.emplace("happyFaceTx", happyFaceTx);

    sf::Texture winFaceTx;
    winFaceTx.loadFromFile("files/images/face_win.png");
    textures.emplace("winFaceTx", winFaceTx);

    sf::Texture loseFaceTx;
    loseFaceTx.loadFromFile("files/images/face_lose.png");
    textures.emplace("loseFaceTx", loseFaceTx);

    sf::Texture debugTx;
    debugTx.loadFromFile("files/images/debug.png");
    textures.emplace("debugTx", debugTx);

    sf::Texture pauseTx;
    pauseTx.loadFromFile("files/images/pause.png");
    textures.emplace("pauseTx", pauseTx);

    sf::Texture playTx;
    playTx.loadFromFile("files/images/play.png");
    textures.emplace("playTx", playTx);

    sf::Texture leaderboardTx;
    leaderboardTx.loadFromFile("files/images/leaderboard.png");
    textures.emplace("leaderboardTx", leaderboardTx);

    sf::Texture digitsTx;
    digitsTx.loadFromFile("files/images/digits.png");
    textures.emplace("digitsTx", digitsTx);

    sf::Texture hiddenTx;
    hiddenTx.loadFromFile("files/images/tile_hidden.png");
    textures.emplace("hiddenTx", hiddenTx);

    sf::Texture revealedTx;
    revealedTx.loadFromFile("files/images/tile_revealed.png");
    textures.emplace("revealedTx", revealedTx);

    sf::Texture flagTx;
    flagTx.loadFromFile("files/images/flag.png");
    textures.emplace("flagTx", flagTx);

    sf::Texture mineTx;
    mineTx.loadFromFile("files/images/mine.png");
    textures.emplace("mineTx", mineTx);

    sf::Texture oneTx;
    oneTx.loadFromFile("files/images/number_1.png");
    textures.emplace("oneTx", oneTx);

    sf::Texture twoTx;
    twoTx.loadFromFile("files/images/number_2.png");
    textures.emplace("twoTx", twoTx);

    sf::Texture threeTx;
    threeTx.loadFromFile("files/images/number_3.png");
    textures.emplace("threeTx", threeTx);

    sf::Texture fourTx;
    fourTx.loadFromFile("files/images/number_4.png");
    textures.emplace("fourTx", fourTx);

    sf::Texture fiveTx;
    fiveTx.loadFromFile("files/images/number_5.png");
    textures.emplace("fiveTx", fiveTx);

    sf::Texture sixTx;
    sixTx.loadFromFile("files/images/number_6.png");
    textures.emplace("sixTx", sixTx);

    sf::Texture sevenTx;
    sevenTx.loadFromFile("files/images/number_7.png");
    textures.emplace("sevenTx", sevenTx);

    sf::Texture eightTx;
    eightTx.loadFromFile("files/images/number_8.png");
    textures.emplace("eightTx", eightTx);
}

sf::Texture& TextureManager::getTx(string name) {
    return textures[name];
}