#include <SFML/Graphics.hpp>
#include "Screen.h"
#include <vector>
#include <iostream>
using namespace std;

int main()
{

    sf::RenderWindow window(sf::VideoMode(1000, 750), "GatorGuesser");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (true) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            cout << "break" << endl;
            break;
        }
    }
   
    
    vector<Screen*> screens;
    Screen titleScreen(false);
    screens.push_back(&titleScreen);
    
    //Title Screen setup



    while (window.isOpen())
    {
        sf::Event event;
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