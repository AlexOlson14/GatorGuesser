#include <SFML/Graphics.hpp>
using namespace std;

int main()
{

    sf::RenderWindow window(sf::VideoMode(1000, 750), "GatorGuesser");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

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

    return 0;
}