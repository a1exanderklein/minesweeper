#include "WelcomeWindow.h"
#include "Leaderboard.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cctype>
#include <vector>

using namespace std;

Leaderboard::Leaderboard(float width, float height) {
    font.loadFromFile("files/font.ttf");
    this -> width = width;
    this -> height = height;
    ifstream infile("files/leaderboard.txt");
    string line;
    while (getline(infile, line)) {
        string time;
        string name;
        stringstream stream(line);
        getline(stream, time, ',');
        getline(stream, name);
        leaders.emplace(time, name);
    }
}

void Leaderboard::operator()(){
    // LEADERBOARD WINDOW //
    sf::RenderWindow leaderboard(sf::VideoMode(width, height), "Leaderboard", sf::Style::Close);

    //Background
    sf::RectangleShape backgroundShape(sf::Vector2f(width, height));
    backgroundShape.setFillColor(sf::Color::Blue);

    //Font
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
        cout << "Failed to load font." << endl;
    }
    
    //Leaderboard Title
    sf::Text messageTitle("LEADERBOARD", font, 20);
    setText(messageTitle, (width/2.0f), (height/2.0f) - 120, true);
    messageTitle.setStyle(sf::Text::Bold | sf::Text::Underlined);

    //Names

    
    while (leaderboard.isOpen()) {
        sf::Event event;
        while (leaderboard.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                leaderboard.close();
            }
            
        }
        leaderboard.clear();
        leaderboard.draw(backgroundShape);
        leaderboard.draw(messageTitle);
        drawLeaders(leaderboard);
        leaderboard.display();
    }
}

void Leaderboard::drawLeaders(sf::RenderWindow& window) {
    sf::Text leaderText("", font, 18);
    leaderText.setStyle(sf::Text::Bold);
    int rank = 1;
    map<string, string>::iterator iter;
    for (iter = leaders.begin(); iter != leaders.end() && rank < 6; iter++) {
        string time = iter->first;
        string name = iter->second;
        string leaderRow = to_string(rank) + ".\t" + time + "\t" + name;
        leaderText.setString(leaderRow);
        setText(leaderText, width/5.0f, height/5.0f + 20 + (40 * (rank - 1)), false);
        window.draw(leaderText);
        rank++;
    }
}

void Leaderboard::setText(sf::Text& text, float x, float y, bool center) {
    if (center) {
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    }
    text.setPosition(sf::Vector2f(x, y));
}

void Leaderboard::addWinner(string name, string time) {
    leaders.emplace(time, name);
    string winner = time + "," + name;
    ofstream outfile("files/leaderboard.txt", ios::app);
    outfile << endl << winner;    
}