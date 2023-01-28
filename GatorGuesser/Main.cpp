#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "TextureManager.h"
#include <vector>
#include <iostream>
#include "ImageProvider.h"
using namespace std;

// Calculate euclidean distance in pixels between two points
int calculateDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// Pixels to feet conversion (for displaying info)
int pixelsToFeet(int pixels) {
    return pixels * 10;
}

// Calculate score based on pixel distance. If within 10 pixels, give 100 bonus points.
int distanceToScore(int distance) {
    int score = 1000 - distance;
    if (score < 0)
        score = 0;
    if (distance < 10)
        score += 100;
    return score;
}

int main()
{

    sf::RenderWindow window(sf::VideoMode(1200, 900), "GatorGuesser");

    

    sf::Sprite loadingScreen;
    loadingScreen.setTexture(TextureManager::getTexture("GatorGuesser"));
    sf::Event event;
    

    vector<Screen*> screens;
    vector<sf::Texture> randomImages;
    




   
   
    
    //Title Screen setup
    Screen titleMenu(true);
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

    sf::CircleShape pin;
    pin.setFillColor(sf::Color::Red);
    pin.setRadius(3);
    ImageProvider imageManager;
    sf::Sprite inFocus(TextureManager::getTexture(imageManager.getImage().name));
    inFocus.scale(1200.0 / 4032.0, 1200.0 / 4032.0);
    gameScreen.spritesToDraw.emplace("image", inFocus);
    sf::Sprite bottomRight(TextureManager::getTexture("map"));
    gameScreen.spritesToDraw.emplace("map", bottomRight);
    //bottomRight.setScale((1 / 3), (1 / 3));
   
    
 

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (titleMenu.needToDraw) {
                        if (titleMenu.spritesToDraw.find("Start")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            titleMenu.needToDraw = false;
                            window.clear();
                            window.draw(loadingScreen);
                            window.display();

                            randomImages.clear();
                            for (int i = 1; i < 2; i++) {
                                string name = imageManager.getImage().name;
                                randomImages.push_back(TextureManager::getTexture(name));
                                cout << "Name: " << name << endl;
                            }

                            gameScreen.needToDraw = true;
                            
                        }
                        else if (titleMenu.spritesToDraw.find("Quit")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            window.close();
                        }
                    }
                    if (gameScreen.needToDraw) {
                        if (gameScreen.spritesToDraw.find("map")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) &&
                            !gameScreen.spritesToDraw.find("image")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            cout << "Clicked on the focused image" << endl;
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
            if (gameScreen.needToDraw) {
                pin.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                window.draw(pin);
            }
        }
        window.display();
    }

    return 0;
}