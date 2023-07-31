#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <cctype>
#include <fstream>
#include <chrono>
#include <vector>
#include "WelcomeWindow.h"
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

void drawCounter(sf::RenderWindow& window, sf::Texture& digitsTx, int numMines, float numCol, float numRow) {
    float x, y;
    int digit1, digit2, digit3;    
    
    digit1 = numMines / 100;
    digit2 = numMines / 10;
    digit3 = numMines % 10;

    x = 33;
    y = 32 * (numRow + 0.5f) + 16;

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

void drawTimer(sf::RenderWindow& window, sf::Texture& digitsTx, float numCol, float numRow, string time) {
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
    // Welcome welcome;
    // welcome();

    // GAME WINDOW //

    //Read Board_config
    float numCol;
    float numRow;
    int numMines;
    ifstream infile("files/board_config.cfg");
    infile >> numCol;
    infile >> numRow;
    infile >> numMines;

    float width = numCol * 32;
    float height = ( numRow * 32 ) + 100;
    float numTiles = numCol * numRow;
    
    sf::RenderWindow game(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);
    
    //Background
    sf::RectangleShape backgroundShape(sf::Vector2f(width, height));
    backgroundShape.setFillColor(sf::Color(200, 200, 200));
    sf::RectangleShape buttonDeck(sf::Vector2f(width, 100));
    buttonDeck.setPosition(0, height - 100);
    buttonDeck.setFillColor(sf::Color::White);

    //Buttons
    sf::Texture happyFaceTx;
    happyFaceTx.loadFromFile("files/images/face_happy.png");
    sf::Texture winFaceTx;
    winFaceTx.loadFromFile("files/images/face_win.png");
    sf::Texture loseFaceTx;
    loseFaceTx.loadFromFile("files/images/face_lose.png");
    sf::Sprite happyFace;
    happyFace.setTexture(happyFaceTx);
    happyFace.setPosition( ((numCol / 2.0) * 32) - 32, 32 *(numRow + 0.5f) );

    sf::Texture debugTx;
    debugTx.loadFromFile("files/images/debug.png");
    sf::Sprite debug;
    debug.setTexture(debugTx);
    debug.setPosition( (numCol * 32) - 304, 32 * (numRow + 0.5f) );

    sf::Texture pauseTx;
    pauseTx.loadFromFile("files/images/pause.png");
    sf::Texture playTx;
    playTx.loadFromFile("files/images/play.png");
    sf::Sprite playButton;
    playButton.setTexture(pauseTx);
    playButton.setPosition( (numCol * 32) - 240, 32 * (numRow + 0.5f) );

    sf::Texture leaderboardTx;
    leaderboardTx.loadFromFile("files/images/leaderboard.png");
    sf::Sprite leaderboard;
    leaderboard.setTexture(leaderboardTx);
    leaderboard.setPosition( (numCol * 32) - 176, 32 * (numRow + 0.5f) );

    //Digits
    sf::Texture digitsTx;
    digitsTx.loadFromFile("files/images/digits.png");

    Timer timer;
    timer.start();
    bool paused = false;

    Board board(game, numTiles, numCol, numRow);
    
    while (game.isOpen()) {
        sf::Event event;
        while (game.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                game.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                auto clickCoordinates = sf::Mouse::getPosition(game);
                cout << "X: " << clickCoordinates.x << endl;
                cout << "Y: " << clickCoordinates.y << endl << endl;

                //Pausing Mechanics
                if (playButton.getGlobalBounds().contains(clickCoordinates.x, clickCoordinates.y)) {
                    paused = !paused;
                    playButton.setTexture(paused ? playTx : pauseTx);
                    if (paused) {
                        timer.pause();
                    }
                    else {
                        timer.resume();
                    }
                }

                //Flagging
                if (backgroundShape.getGlobalBounds().contains(clickCoordinates.x, clickCoordinates.y)) {
                    if (event.mouseButton.button == sf::Mouse::Right) {
                        int col = static_cast<int>(clickCoordinates.x) / 32;
                        int row = static_cast<int>(clickCoordinates.y) / 32;
                        int tileNumber = static_cast<int>(numCol * row + col);
                        board.setFlag(tileNumber);
                    }
                }
            }
        }
        game.clear();
        game.draw(backgroundShape);
        game.draw(buttonDeck);
        board.drawBoard();
        game.draw(happyFace);
        game.draw(debug);
        game.draw(playButton);
        game.draw(leaderboard);
        drawCounter(game, digitsTx, numMines, numCol, numRow);
        drawTimer(game, digitsTx, numCol, numRow, timer.getTime());
        game.display();
    }

    return 0;
}