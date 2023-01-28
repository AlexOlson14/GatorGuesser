#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "TextureManager.h"
#include <vector>
#include <iostream>
using namespace std;

int main()
{

    sf::RenderWindow window(sf::VideoMode(1200, 900), "GatorGuesser");
    vector<Screen*> screens;


    sf::Sprite splashScreen;
    //splashScreen.setTextureRect(sf::IntRect(0, 0, 1000, 750));
    splashScreen.setTexture(TextureManager::getTexture("GatorGuesser"));
    //splashScreen.set
    sf::Event event;
    bool needToBreak = false;


    
    



    //splash scrren stuff
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
    Screen titleMenu(true);
    sf::Sprite playButton(TextureManager::getTexture("playButton"));
    playButton.setPosition(600, 300);

    sf::Sprite exitButton(TextureManager::getTexture("exitButton"));
    exitButton.setPosition(600, 500);

    titleMenu.spritesToDraw.emplace("playButton", playButton);
    titleMenu.spritesToDraw.emplace("exitButton", exitButton);

    Screen gameMenu(false);
    sf::Sprite inFocus;
    sf::Sprite bottomRight;



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
                    if (titleMenu.needToDraw) {
                        
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        for (int i = 0; i < screens.size(); i++) {
            if (screens.at(i)->needToDraw) {
                screens.at(i)->showScreen(window);
            }
        }
        window.display();
    }

    return 0;
}