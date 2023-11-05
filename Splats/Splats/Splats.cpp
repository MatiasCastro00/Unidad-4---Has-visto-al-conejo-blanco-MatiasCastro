#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
using namespace std;
using namespace sf;
Texture textureB;
Texture textureR;
Sprite cirlce;
int main()
{
	textureB.loadFromFile("rcircle.png");
	textureR.loadFromFile("rcircleb.png");
	int width = 800;
	int height = 600;
	list<Sprite> objects;
	sf::RenderWindow App(sf::VideoMode(width, height, 32),
		"Sniper");
	while (App.isOpen())
	{
		App.clear();

		Event event;
		while (App.pollEvent(event)) {
			// Existing event handling code...
			if (event.type == Event::MouseButtonPressed) {
				Vector2i mousePos = Mouse::getPosition(App);
				Sprite NewCircle;

				NewCircle.setPosition((float)(mousePos.x), (float)(mousePos.y));
				if (event.mouseButton.button == Mouse::Left) {
					NewCircle.setTexture(textureB);
				}
				if (event.mouseButton.button == Mouse::Right) {
					NewCircle.setTexture(textureR);
				}
				NewCircle.setOrigin(NewCircle.getLocalBounds().width / 2, NewCircle.getLocalBounds().height / 2);
				objects.push_back(NewCircle);

			}
		}
		for (auto it = objects.begin(); it != objects.end(); ++it) {
			App.draw(*it);
		}
		App.display();
	}
	return 0;
}
