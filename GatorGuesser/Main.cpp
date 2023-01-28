#include <SFML/Graphics.hpp>
#include "Screen.h"
#include <vector>
using namespace std;

int main()
{

    sf::RenderWindow window(sf::VideoMode(1000, 750), "GatorGuesser");


    sf::Event event;
    while(window.pollEvent(event)){
        if (event.type == sf::Event::MouseButtonPressed){
            break;
        }
    }
    vector<Screen*> screens;
    Screen titleScreen(false);
    screens.push_back(&titleScreen);
    
    //Title Screen setup


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

        window.clear();

        window.display();

    }

    return 0;
}