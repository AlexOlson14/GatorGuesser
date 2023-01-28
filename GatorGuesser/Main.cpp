#include <SFML/Graphics.hpp>
using namespace std;

int main()
{

	sf::RenderWindow window(sf::VideoMode(600, 800), "GatorGuesser");
	while (window.isOpen())
	{
		window.clear();

		window.display();



	}


	return 0;
}