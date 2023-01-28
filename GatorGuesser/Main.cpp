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

    

    sf::Sprite splashScreen;
    //splashScreen.setTextureRect(sf::IntRect(0, 0, 1000, 750));
    splashScreen.setTexture(TextureManager::getTexture("GatorGuesser"));
    //splashScreen.set
    sf::Event event;
    window.draw(splashScreen);
    window.display();
    bool needToBreak = false;


    vector<Screen*> screens;
    vector<sf::Texture> randomImages;
    for (int i = 1; i < 6; i++) {
        randomImages.push_back(TextureManager::getTexture("sam" + to_string(i)));
    }




   
   
    
    //Title Screen setup
    Screen titleMenu(false);
    screens.push_back(&titleMenu);
    sf::Sprite Start(TextureManager::getTexture("Start"));
    Start.setPosition(650, 350);

    sf::Sprite Quit(TextureManager::getTexture("Quit"));
    Quit.setPosition(650, 550);

    sf::Sprite TitleScreen(TextureManager::getTexture("TitleScreen"));


    titleMenu.spritesToDraw.emplace("background", TitleScreen);
    titleMenu.spritesToDraw.emplace("Start", Start);
    titleMenu.spritesToDraw.emplace("Quit", Quit);
    

    Screen gameScreen(false);
    screens.push_back(&gameScreen);
    ImageProvider imageManager;
    sf::Sprite inFocus(TextureManager::getTexture(imageManager.getImage().name));
    sf::Sprite bottomRight(TextureManager::getTexture("map"));
    //bottomRight.setScale((1 / 3), (1 / 3));
   
    
    //splash screen stuff
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
            titleMenu.needToDraw = true;
            break;
        }
        window.clear();
        window.draw(splashScreen);
        window.display();
    }

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
                        if (titleMenu.spritesToDraw.find("Start")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            titleMenu.needToDraw = false;
                            gameScreen.needToDraw = true;
                            cout << "Clicked";
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