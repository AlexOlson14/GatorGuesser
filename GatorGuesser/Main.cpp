#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "TextureManager.h"
#include <vector>
#include <iostream>
#include "ImageProvider.h"
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

    Screen gameScreen(false);
    ImageProvider imageManager;
    sf::Sprite inFocus(TextureManager::getTexture(imageManager.getImage().name));
    sf::Sprite bottomRight(TextureManager::getTexture("map"));
    bottomRight.setScale((1 / 3), (1 / 3));
   
    


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
                        if (titleMenu.spritesToDraw.find("playButton")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            titleMenu.needToDraw = true;
                            gameScreen.needToDraw = false;
                        }
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