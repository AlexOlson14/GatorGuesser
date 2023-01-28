#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "TextureManager.h"
#include <vector>
#include <iostream>
using namespace std;

int main()
{

    sf::RenderWindow window(sf::VideoMode(1000, 750), "GatorGuesser");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    vector<Screen*> screens;
    sf::Sprite splashScreen;
    //splashScreen.setTextureRect(sf::IntRect(0, 0, 1000, 750));
    splashScreen.setTexture(TextureManager::getTexture("GatorGuesser"));
    //splashScreen.set
    sf::Event event;
    bool needToBreak = false;

    while (true) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    needToBreak = true;
                }
            }
        }
        if (needToBreak)
        {
            break;
        }
        window.clear();
        window.draw(splashScreen);
        window.display();
    }
   
    
    //Title Screen setup
    Screen titleMenu(false);


    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {

                }
                if (event.mouseButton.button == sf::Mouse::Left)
                {

                }
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}