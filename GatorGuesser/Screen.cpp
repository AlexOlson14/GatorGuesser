#include "Screen.h"
#include <iostream>

Screen::Screen() {
    this->needToDraw = false;
}
Screen::Screen(bool showScreenOnCreation) {
    needToDraw = showScreenOnCreation;
    //_font->loadFromFile("../testSWEProject/src/Font/OpenSans-Regular.ttf");
}

Screen::~Screen() { //not sure if I need this.
    for (auto it = text.begin(); it != text.end(); ++it) delete it->second;
    delete _font;
}

void Screen::showScreen(sf::RenderWindow& w) {
    if (spritesToDraw.find("background") != spritesToDraw.end()) {
        w.draw(spritesToDraw.find("background")->second);
    }
    for (auto i = spritesToDraw.begin(); i != spritesToDraw.end(); i++) {
        if (i->first != "background") {
            w.draw(i->second);
        }
    }
    for (auto it = text.begin(); it != text.end(); ++it) {
        w.draw(*it->second);
    }
}

void Screen::setText(string text_to_output, string where_to_display) {
    cout << text_to_output;
    sf::Text* _text = new sf::Text();
    _text->setFont(*_font);
    _text->setString(text_to_output);
    _text->setCharacterSize(35);
    _text->setFillColor(sf::Color::Black);
    sf::FloatRect textRect = _text->getLocalBounds();
    sf::FloatRect RectangleShapeRect = spritesToDraw[where_to_display].getLocalBounds();
    _text->setPosition(spritesToDraw[where_to_display].getPosition().x + (RectangleShapeRect.width / 2 - textRect.width / 2),
        spritesToDraw[where_to_display].getPosition().y + (RectangleShapeRect.height / 2 - 25));
    text[spritesToDraw[where_to_display].getPosition().x * spritesToDraw[where_to_display].getPosition().y] = _text;
}