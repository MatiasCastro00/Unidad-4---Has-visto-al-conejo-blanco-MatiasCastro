#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <cstdlib> 
#include "Clickale.h"
using namespace std;
using namespace sf;

Texture crosshairTexture;
Texture etTexture;
Sprite crosshair;


void CreateEnemies(int enemyAmmount, int width, int height, std::list<sf::Sprite>& enemies)
{
	for (size_t i = 0; i < enemyAmmount; i++)
	{
		Sprite Et;
		float randomX = rand() % width;
		float randomy = rand() % height;
		Et.setTexture(etTexture);
		Et.setOrigin(Et.getLocalBounds().width / 2, Et.getLocalBounds().height / 2);
		Et.setPosition(randomX, randomy);
		Et.setScale(0.1, 0.1);
		enemies.push_back(Et);
	}
}

int main() {
	crosshairTexture.loadFromFile("crosshair.png");
	etTexture.loadFromFile("et.png");
	crosshair.setTexture(crosshairTexture);
	crosshair.setScale(0.5, 0.5);
	crosshair.setOrigin(crosshair.getLocalBounds().width / 2, crosshair.getLocalBounds().height / 2);
	int width = 1000;
	int height = 800;
	sf::RenderWindow App(sf::VideoMode(width, height, 32),
		"Sniper");
	int enemyAmmount=5;
	list<Sprite> enemies;
	CreateEnemies(enemyAmmount, width, height, enemies);
	while (App.isOpen())
	{
		App.clear();
		App.setMouseCursorVisible(false);
		Event event;
		while (App.pollEvent(event)) {
			if (event.type == Event::Closed)
				App.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					Vector2i mousePos = Mouse::getPosition(App);
					auto it = enemies.begin();
					while (it != enemies.end())
					{
						if (it->getGlobalBounds().contains(Vector2f(mousePos.x, mousePos.y)))
						{
							it = enemies.erase(it);
						}
						else
						{
							++it;
						}
					}
				}
			}
		}
		Vector2i mousePos  = Mouse::getPosition(App);
		crosshair.setPosition((float)(mousePos.x), (float)(mousePos.y));
		for (auto it = enemies.begin(); it != enemies.end(); ++it) {
			App.draw(*it);
		}
		if(enemies.size()<=0)
			CreateEnemies(enemyAmmount, width, height, enemies);
		App.draw(crosshair);
		App.display();
	}
	return 0;
}