#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <cctype>
#include <fstream>
#include <chrono>
#include <vector>
#include "WelcomeWindow.h"
#include "Leaderboard.h"
#include "TextureManager.h"
#include "tiles.h"
#include "board.h"

using namespace std;

class Timer {
public:
    void start() {
        //begin timer
        startTime = chrono::high_resolution_clock::now();
        running = true;
    }

    void pause() {
        //if currently running
        if (running) {
            //when paused, add the elapsed time to the total for displaying
            tempTime = chrono::high_resolution_clock::now();
            totalTime += tempTime - startTime;
            running = false;
        }
    }

    void resume() {
        //if not running
        if (!running) {
            //resets startTime to hold new time point
            startTime = chrono::high_resolution_clock::now();
            running = true;
        }
    }

    void reset() {
        startTime = chrono::high_resolution_clock::now();
        totalTime = std::chrono::high_resolution_clock::duration::zero();
        running = false;
    }

    string stop() {
        tempTime = chrono::high_resolution_clock::now();
        totalTime += tempTime - startTime;
        running = false;
        string finalTime = getTime();
        return finalTime;
    }
    
    string getTime() {
        if (running) {
            //time that has passed
            auto currentTime = chrono::high_resolution_clock::now();
            //add total elapsed to the time that has passed since last start
            auto duration = totalTime + (currentTime - startTime);
            int secondsTotal = chrono::duration_cast<chrono::seconds>(duration).count();
            string clock = "";
            int minutes = (secondsTotal / 60);
            int seconds = (secondsTotal % 60);
            if (minutes < 10) {
                clock += "0";
            }
            clock += to_string(minutes);
            if (seconds < 10) {
                clock += "0";
            }
            clock += to_string(seconds);
            return clock;
        }
        else {
            int secondsTotal = chrono::duration_cast<chrono::seconds>(totalTime).count();
            string clock = "";
            int minutes = (secondsTotal / 60);
            int seconds = (secondsTotal % 60);
            if (minutes < 10) {
                clock += "0";
            }
            clock += to_string(minutes);
            if (seconds < 10) {
                clock += "0";
            }
            clock += to_string(seconds);
            return clock;
        }
    }

private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point tempTime;
    std::chrono::high_resolution_clock::duration totalTime = std::chrono::high_resolution_clock::duration::zero();
    bool running = false;
};

void drawCounter(sf::RenderWindow& window, sf::Texture& digitsTx, int numMines, int numFlags, int numCol, int numRow) {
    int count = numMines - numFlags;
    
    float x, y;
    int digit1, digit2, digit3;    
    
    digit1 = abs(count / 100);
    digit2 = abs(count / 10);
    digit3 = abs(count % 10);

    x = 33;
    y = 32 * (numRow + 0.5f) + 16;

    if (count < 0) {
        digit1 = 10;
    }

    sf::IntRect rect1(digit1 * 21, 0, 21, 32);
    sf::Sprite digitSprite1(digitsTx, rect1);
    digitSprite1.setPosition(x, y);
    window.draw(digitSprite1);

    sf::IntRect rect2(digit2 * 21, 0, 21, 32);
    sf::Sprite digitSprite2(digitsTx, rect2);
    digitSprite2.setPosition(x + 21, y);
    window.draw(digitSprite2);

    sf::IntRect rect3(digit3 * 21, 0, 21, 32);
    sf::Sprite digitSprite3(digitsTx, rect3);
    digitSprite3.setPosition(x + 42, y);
    window.draw(digitSprite3);
}

void drawTimer(sf::RenderWindow& window, sf::Texture& digitsTx, int numCol, int numRow, string time) {
    int min1 = time[0] - '0';
    int min2 = time[1] - '0';
    float minX, minY;
    minX = ((numCol) * 32) - 97;
    minY = 32 * ((numRow) + 0.5f) + 16;
    sf::IntRect rect1(min1 * 21, 0, 21, 32);
    sf::Sprite digitSprite1(digitsTx, rect1);
    digitSprite1.setPosition(minX, minY);
    window.draw(digitSprite1);

    sf::IntRect rect2(min2 * 21, 0, 21, 32);
    sf::Sprite digitSprite2(digitsTx, rect2);
    digitSprite2.setPosition(minX + 21, minY);
    window.draw(digitSprite2);

    int sec1 = time[2] - '0';
    int sec2 = time[3] - '0';
    float secX, secY;
    secX = ((numCol) * 32) - 54;
    secY = 32 * ((numRow) + 0.5f) + 16;
    sf::IntRect rect3(sec1 * 21, 0, 21, 32);
    sf::Sprite digitSprite3(digitsTx, rect3);
    digitSprite3.setPosition(secX, secY);
    window.draw(digitSprite3);

    sf::IntRect rect4(sec2 * 21, 0, 21, 32);
    sf::Sprite digitSprite4(digitsTx, rect4);
    digitSprite4.setPosition(secX + 21, secY);
    window.draw(digitSprite4);
}

int main() {
    TextureManager txm;
    //Read Board_config
    int numCol;
    int numRow;
    int numMines;
    ifstream infile("files/board_config.cfg");
    infile >> numCol;
    infile >> numRow;
    infile >> numMines;
    float width = numCol * 32;
    float height = ( numRow * 32 ) + 100;
    float numTiles = numCol * numRow; 

    Welcome welcome;
    welcome(width, height);
    string namePlayer = welcome.getName();
    // string namePlayer = "A";

    // GAME WINDOW //
    sf::RenderWindow game(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);
    
    //Background
    sf::RectangleShape backgroundShape(sf::Vector2f(width, height - 100));
    backgroundShape.setFillColor(sf::Color(200, 200, 200));
    sf::RectangleShape buttonDeck(sf::Vector2f(width, 100));
    buttonDeck.setPosition(0, height - 100);
    buttonDeck.setFillColor(sf::Color::White);

    //Buttons
    sf::Sprite happyFace;
    happyFace.setTexture(txm.getTx("happyFaceTx"));
    happyFace.setPosition( ((numCol / 2.0) * 32) - 32, 32 *(numRow + 0.5f) );

    sf::Sprite debug;
    debug.setTexture(txm.getTx("debugTx"));
    debug.setPosition( (numCol * 32) - 304, 32 * (numRow + 0.5f) );

    sf::Sprite playButton;
    playButton.setTexture(txm.getTx("pauseTx"));
    playButton.setPosition( (numCol * 32) - 240, 32 * (numRow + 0.5f) );

    sf::Sprite leaderboardSprite;
    leaderboardSprite.setTexture(txm.getTx("leaderboardTx"));
    leaderboardSprite.setPosition( (numCol * 32) - 176, 32 * (numRow + 0.5f) );

    Timer timer;
    timer.start();
    bool paused = false;
    bool debugging = false;
    bool gameLost = false;
    string finalTime = "";

    Board board(game, txm, numMines, numTiles, numCol, numRow);
    Leaderboard leaderboard(width/2.0f, height/2.0f);
    
    while (game.isOpen()) {
        sf::Event event;
        int numFlags = board.getNumFlags();
        while (game.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                game.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                auto clickCoordinates = sf::Mouse::getPosition(game);
                if (board.checkOver() == false && board.checkWin() == false && paused == false) {
                    //Flagging & Revealing
                    if (backgroundShape.getGlobalBounds().contains(clickCoordinates.x, clickCoordinates.y)) {
                        if (event.mouseButton.button == sf::Mouse::Right) {
                            int col = static_cast<int>(clickCoordinates.x) / 32;
                            int row = static_cast<int>(clickCoordinates.y) / 32;
                            int tileNumber = static_cast<int>(numCol * row + col);
                            board.setFlag(tileNumber);
                        }
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            int col = static_cast<int>(clickCoordinates.x) / 32;
                            int row = static_cast<int>(clickCoordinates.y) / 32;
                            int tileNumber = static_cast<int>(numCol * row + col);
                            board.setReveal(tileNumber);
                            // cout << "Tile Number : " << tileNumber << endl;
                            board.checkOver();
                            if (board.checkOver() == true) {
                                gameLost = true;
                                happyFace.setTexture(txm.getTx("loseFaceTx"));
                                finalTime = timer.stop();
                            }
                            board.checkWin();
                            if (board.checkWin() == true) {
                                board.setWinFlag();
                                happyFace.setTexture(txm.getTx("winFaceTx"));
                                debugging = false;
                                finalTime = timer.stop();
                                finalTime.insert(2, ":");
                                leaderboard.addWinner(namePlayer, finalTime);
                            } 
                        }
                    }
                }
                if (board.checkOver() == false && board.checkWin() == false) {
                    //Pausing Mechanics
                    if (playButton.getGlobalBounds().contains(clickCoordinates.x, clickCoordinates.y)) {
                        paused = !paused;
                        playButton.setTexture(paused ? txm.getTx("playTx") : txm.getTx("pauseTx"));
                        if (paused) {
                            timer.pause();
                        }
                        else {
                            timer.resume();
                        }
                    }
                    //Debug Button
                    if (debug.getGlobalBounds().contains(clickCoordinates.x, clickCoordinates.y)) {
                        debugging = !debugging;
                    }
                }
                if (happyFace.getGlobalBounds().contains(clickCoordinates.x, clickCoordinates.y)) {
                    board.reset(txm);
                    finalTime = "";
                    timer.reset();
                    paused = false;
                    playButton.setTexture(txm.getTx("pauseTx"));
                    timer.start();
                    happyFace.setTexture(txm.getTx("happyFaceTx"));
                    gameLost = false;
                    debugging = false;
                }
                if (board.checkOver() == false && leaderboardSprite.getGlobalBounds().contains(clickCoordinates.x, clickCoordinates.y)) {
                    timer.pause();
                    board.drawBoard(true, false, false );
                    game.display();
                    leaderboard();
                    if (paused == false) {
                        timer.resume();                         
                    }
                }
                if (board.checkOver() == true && leaderboardSprite.getGlobalBounds().contains(clickCoordinates.x, clickCoordinates.y)) {
                    leaderboard();
                }
            }
        }
        game.clear();
        game.draw(backgroundShape);
        game.draw(buttonDeck);
        board.drawBoard(paused, debugging, gameLost);
        game.draw(happyFace);
        game.draw(debug);
        game.draw(playButton);
        game.draw(leaderboardSprite);
        drawCounter(game, txm.getTx("digitsTx"), numMines, numFlags, numCol, numRow);
        drawTimer(game, txm.getTx("digitsTx"), numCol, numRow, timer.getTime());
        game.display();
    }

    return 0;
}