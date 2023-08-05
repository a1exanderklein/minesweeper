#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using namespace std;

class TextureManager {
public:
    TextureManager();
    sf::Texture& getTx(string name);

private:
    unordered_map<string, sf::Texture> textures;
};