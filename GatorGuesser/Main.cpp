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
    
    sf::Texture map = TextureManager::getTexture("map");

    sf::Font font;
    if (!font.loadFromFile("OpenSans-Regular.ttf"))
    {
        cout << "problem loading font" << endl;
    }
    sf::Text text;

    // select the font
    text.setFont(font); // font is a sf::Font

    // set the character size
    text.setCharacterSize(40); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Black);
    
    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);


        // inside the main loop, between window.clear() and window.display()
        window.draw(text);






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
    bool movingPin = true;
    screens.push_back(&gameScreen);

    sf::CircleShape pin;
    pin.setFillColor(sf::Color::Red);
    pin.setRadius(3);
    pin.setOrigin(pin.getRadius(), pin.getRadius());


    ImageProvider imageManager;

    sf::Sprite focus;
    sf::Sprite noFocus;

    focus.setScale(1200.0 / 4032.0, 1200.0 / 4032.0);
    noFocus.setScale(1.0 / 4.0, 1.0 / 4.0);
    noFocus.setPosition(850, 650);


    gameScreen.spritesToDraw.emplace("background", focus);
    gameScreen.spritesToDraw.emplace("picture", noFocus);
    int counter = 0;


    Screen answerScreen(false);
    screens.push_back(&answerScreen);
    
    sf::Sprite bigMap(TextureManager::getTexture("map"));
    sf::CircleShape correctSpot;
    correctSpot.setRadius(10);
    correctSpot.setFillColor(sf::Color::Blue);
    correctSpot.setOrigin(correctSpot.getRadius(), correctSpot.getRadius());

    answerScreen.spritesToDraw.emplace("background", bigMap);
    
    bool lookingAtPicture = true;

    Screen pointScreen(false);
    screens.push_back(&pointScreen);

    sf::Sprite returnBtn(TextureManager::getTexture("Return"));
    returnBtn.setPosition(400, 500);
    sf::Sprite background(TextureManager::getTexture("points"));
    sf::Sprite pointThing(TextureManager::getTexture("Score"));
    pointThing.setPosition(400, 300);
    
    pointScreen.spritesToDraw.emplace("background", background);
    pointScreen.spritesToDraw.emplace("button", returnBtn);
    pointScreen.spritesToDraw.emplace("text", pointThing);
    int points = 0;


    vector<Image> images;


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
                            images.clear();
                            for (int i = 1; i < 6; i++) {
                                Image image = imageManager.getImage();
                                images.push_back(image);
                                randomImages.push_back(TextureManager::getTexture(image.name));
                            }

                            gameScreen.needToDraw = true;
                            gameScreen.spritesToDraw.find("background")->second.setTexture(randomImages[0]);    
                            gameScreen.spritesToDraw.find("picture")->second.setTexture(map);
                            counter = 0;
                        }
                        else if (titleMenu.spritesToDraw.find("Quit")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            window.close();
                        }
                    }


                    else if (gameScreen.needToDraw) {
                        //Switch the events
                        if (gameScreen.spritesToDraw.find("picture")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            if (!lookingAtPicture)
                            {
                                gameScreen.spritesToDraw.erase("background");
                                gameScreen.spritesToDraw.erase("picture");

                                sf::Sprite background;
                                sf::Sprite picture;

                                background.setScale(1200.0 / 4032.0, 1200.0 / 4032.0);
                                picture.setScale(1.0 / 4.0, 1.0 / 4.0);
                                picture.setPosition(850, 650);

                                background.setTexture(randomImages[counter]);
                                picture.setTexture(map);

                                gameScreen.spritesToDraw.emplace("background", background);
                                gameScreen.spritesToDraw.emplace("picture", picture);
                                lookingAtPicture = !lookingAtPicture;
                            }
                            else
                            {
                                gameScreen.spritesToDraw.erase("background");
                                gameScreen.spritesToDraw.erase("picture");

                                sf::Sprite background;
                                sf::Sprite picture;

                                background.setScale(1, 1);
                                picture.setScale(1200.0 / 4032.0 / 4.0, 1200.0 / 4032.0 / 4.0);
                                picture.setPosition(850, 650);

                                background.setTexture(map);
                                picture.setTexture(randomImages[counter]);

                                gameScreen.spritesToDraw.emplace("background", background);
                                gameScreen.spritesToDraw.emplace("picture", picture);
                                lookingAtPicture = !lookingAtPicture;
                            }
                        }


                        else if (counter < randomImages.size() - 1 && !lookingAtPicture) //not last
                        {
                            counter++;

                           

                            gameScreen.spritesToDraw.erase("background");
                            gameScreen.spritesToDraw.erase("picture");

                            sf::Sprite background;
                            sf::Sprite picture;

                            background.setScale(1200.0 / 4032.0, 1200.0 / 4032.0);
                            picture.setScale(1.0 / 4.0, 1.0 / 4.0);
                            picture.setPosition(850, 650);

                            background.setTexture(randomImages[counter]);
                            picture.setTexture(map);

                            gameScreen.spritesToDraw.emplace("background", background);
                            gameScreen.spritesToDraw.emplace("picture", picture);
                            lookingAtPicture = true;
                            
                            gameScreen.needToDraw = false;
                            answerScreen.needToDraw = true;
                            correctSpot.setPosition(images.at(counter).location.second, images.at(counter).location.first);

                        }
                        else if (counter == randomImages.size() - 1 && !lookingAtPicture) //last one
                        {
                            pointScreen.needToDraw = true;
                            gameScreen.needToDraw = false;
                            //dont show title screen, show answer screen then show final score screen

                        }
                    }
                    else if (answerScreen.needToDraw) {
                        int distance = calculateDistance(pin.getPosition().x, pin.getPosition().y, correctSpot.getPosition().x, correctSpot.getPosition().y);
                        int tempPoints = distanceToScore(distance);
                        points += tempPoints;
                        if (answerScreen.spritesToDraw.find("background")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            if (counter == randomImages.size() - 1) //last one
                            {
                                pointScreen.needToDraw = true;
                                answerScreen = false;
                                string result = to_string(points);
                                result += " / 5500";
                                // set the string to display
                                text.setString(result);
                                sf::FloatRect textRect = text.getLocalBounds();
                                text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                                text.setPosition(sf::Vector2f(pointScreen.spritesToDraw.find("text")->second.getGlobalBounds().width / 2.0f, pointScreen.spritesToDraw.find("text")->second.getGlobalBounds().height / 2.0f));
                                
                            }
                            else
                            {
                                answerScreen.needToDraw = false;
                                gameScreen.needToDraw = true;
                            }
                        }
                    }
                    else if (pointScreen.needToDraw)
                    {
                    answerScreen.spritesToDraw.emplace("background", bigMap);
                        if (pointScreen.spritesToDraw.find("button")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            titleMenu.needToDraw = true;
                            pointScreen.needToDraw = false;
                            counter = 0;
                            points = 0; 
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
                if (movingPin) {
                    pin.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                }
                if(!lookingAtPicture){
                    window.draw(pin);
                }
            }
            if (answerScreen.needToDraw) {
                window.draw(pin);
                window.draw(correctSpot);
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(pin.getPosition().x, pin.getPosition().y)),
                    sf::Vertex(sf::Vector2f(correctSpot.getPosition().x, correctSpot.getPosition().y))
                };

                
                line[0].color = sf::Color::Magenta;
                line[1].color = sf::Color::Magenta;
                window.draw(line, 2, sf::Lines);
            }
        }
        if (pointScreen.needToDraw)
        {
            window.draw(text);
        }
        window.display();
    }

    return 0;
}