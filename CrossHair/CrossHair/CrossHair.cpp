#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

Texture textureNew;
Texture textureCenter;
Sprite circleNew;
int main()
{
	int width = 800;
	int height = 600;
	sf::RenderWindow App(sf::VideoMode(800, 600, 600),
		"Sniper");
	while (App.isOpen())
	{
		// Limpiamos la ventana
		App.clear();

		textureCenter.loadFromFile("crosshair.png");
		circleNew.setTexture(textureCenter);
		circleNew.setOrigin(circleNew.getLocalBounds().width / 2, circleNew.getLocalBounds().height / 2);
		circleNew.setPosition(width / 2, height / 2);
		App.draw(circleNew);
		App.display();
	}

}


