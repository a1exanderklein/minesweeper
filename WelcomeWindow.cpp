#include "WelcomeWindow.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cctype>

void Welcome::operator()(float width, float height){
    // WELCOME WINDOW //
    sf::RenderWindow welcome(sf::VideoMode(width, height), "Welcome Window", sf::Style::Close);

    //Background
    sf::RectangleShape backgroundShape(sf::Vector2f(width, height));
    backgroundShape.setFillColor(sf::Color::Blue);

    //Font
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
        cout << "Failed to load font." << endl;
    }
    
    //Welcome Message
    sf::Text messageWelcome("WELCOME TO MINESWEEPER!", font, 24);
    setText(messageWelcome, (width/2.0f), (height/2.0f) - 150);
    messageWelcome.setStyle(sf::Text::Bold | sf::Text::Underlined);

    //Input Message
    sf::Text messageInput("Enter your name:", font, 20);
    setText(messageInput, (width/2.0f), (height/2.0f) - 75);
    messageInput.setStyle(sf::Text::Bold);

    //Name Input Text
    sf::Text nameInput("", font, 18);
    nameInput.setFillColor(sf::Color::Yellow);
    setText(nameInput, (width/2.0f), (height/2.0f) - 45);
    nameInput.setStyle(sf::Text::Bold);

    //Cursor
    sf::Text cursor("|", font, 18);
    cursor.setFillColor(sf::Color::Yellow);
    setText(cursor, (width/2.0f), (height/2.0f) - 45);
    cursor.setStyle(sf::Text::Bold);

    namePlayer = "";
    
    while (welcome.isOpen()) {
        sf::Event event;
        while (welcome.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                exit(EXIT_SUCCESS);
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128 && isalpha(static_cast<char>(event.text.unicode))) {
                    if (namePlayer.size() < 10) {
                        namePlayer += static_cast<char>(event.text.unicode);
                    }
                }
                if (event.text.unicode == 8) { //code for backspace
                    if (namePlayer.size() > 0) {
                        namePlayer.pop_back();
                    }
                }
                setCasing(namePlayer);
                nameInput.setString(namePlayer);
                setText(nameInput, (width/2.0f), (height/2.0f) - 45);
                sf::FloatRect nameInputRect = nameInput.getLocalBounds();
                float cursorX = nameInput.getPosition().x + nameInputRect.width * 0.5f + 3.0f; //space beween cursor and name
                float cursorY = nameInput.getPosition().y;
                cursor.setPosition(cursorX, cursorY);
            }
            if (event.type == sf::Event::KeyPressed) {
                if (namePlayer.size() > 0) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        welcome.close();
                    }
                }
            }
        }
        welcome.clear();
        welcome.draw(backgroundShape);
        welcome.draw(messageWelcome);
        welcome.draw(messageInput);
        welcome.draw(cursor);
        welcome.draw(nameInput);
        welcome.display();
    }
}

void Welcome::setText(sf::Text& text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void Welcome::setCasing(std::string& name) {
    if (name.size() > 0) {
        name[0] = std::toupper(name[0]);
        for (int i = 1; i < name.size(); i++) {
            name[i] = std::tolower(name[i]);
        }
    }
}

// void setText(sf::Text &text, float x, float y){
//     sf::FloatRect textRect = text.getLocalBounds();
//     text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
//     text.setPosition(sf::Vector2f(x, y));
// }

// void setCasing(string& name) {
//     if (name.size() > 0) {
//         name[0] = toupper(name[0]);
//         for (int i = 1; i < name.size(); i++) {
//             name[i] = tolower(name[i]);
//         }
//     }
// }

// // WELCOME WINDOW //
// sf::RenderWindow welcome(sf::VideoMode(800, 600), "Welcome Window", sf::Style::Close);

// //Background
// sf::RectangleShape backgroundShape(sf::Vector2f(800, 600));
// backgroundShape.setFillColor(sf::Color::Blue);

// //Font
// sf::Font font;
// if (!font.loadFromFile("files/font.ttf")) {
//     return EXIT_FAILURE;
// }

// //Welcome Message
// sf::Text messageWelcome("WELCOME TO MINESWEEPER!", font, 24);
// setText(messageWelcome, (800/2.0f), (600/2.0f) - 150);
// messageWelcome.setStyle(sf::Text::Bold | sf::Text::Underlined);

// //Input Message
// sf::Text messageInput("Enter your name:", font, 20);
// setText(messageInput, (800/2.0f), (600/2.0f) - 75);
// messageInput.setStyle(sf::Text::Bold);

// //Name Input Text
// sf::Text nameInput("", font, 18);
// nameInput.setFillColor(sf::Color::Yellow);
// setText(nameInput, (800/2.0f), (600/2.0f) - 45);
// nameInput.setStyle(sf::Text::Bold);

// //Cursor
// sf::Text cursor("|", font, 18);
// cursor.setFillColor(sf::Color::Yellow);
// setText(cursor, (800/2.0f), (600/2.0f) - 45);
// cursor.setStyle(sf::Text::Bold);

// string namePlayer = "";

// while (welcome.isOpen()) {
//     sf::Event event;
//     while (welcome.pollEvent(event)) {
//         if (event.type == sf::Event::Closed)
//             welcome.close();
//         if (event.type == sf::Event::TextEntered) {
//             if (event.text.unicode < 128 && isalpha(static_cast<char>(event.text.unicode))) {
//                 if (namePlayer.size() < 10) {
//                     namePlayer += static_cast<char>(event.text.unicode);
//                 }
//             }
//             if (event.text.unicode == 8) { //code for backspace
//                 if (namePlayer.size() > 0) {
//                     namePlayer.pop_back();
//                 }
//             }
//             setCasing(namePlayer);
//             nameInput.setString(namePlayer);
//             setText(nameInput, (800/2.0f), (600/2.0f) - 45);
//             sf::FloatRect nameInputRect = nameInput.getLocalBounds();
//             float cursorX = nameInput.getPosition().x + nameInputRect.width * 0.5f + 3.0f; //space beween cursor and name
//             float cursorY = nameInput.getPosition().y;
//             cursor.setPosition(cursorX, cursorY);
//         }
//         if (event.type == sf::Event::KeyPressed) {
//             if (event.key.code == sf::Keyboard::Enter) {
//                 welcome.close();
//             }
//         }
//     }
//     welcome.clear();
//     welcome.draw(backgroundShape);
//     welcome.draw(messageWelcome);
//     welcome.draw(messageInput);
//     welcome.draw(cursor);
//     welcome.draw(nameInput);
//     welcome.display();
// }