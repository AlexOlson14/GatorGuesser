#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <unordered_map>

using namespace std;
struct Screen
{
    bool needToDraw;
    map<string, sf::Sprite> spritesToDraw;
    Screen();
    Screen(bool a);
    ~Screen();
    void showScreen(sf::RenderWindow& w);
    void setText(string text_to_output, string where_to_display);

private:
    // use for setText function
    unordered_map<int, sf::Text*> text;
    sf::Font* _font = new sf::Font;
};



