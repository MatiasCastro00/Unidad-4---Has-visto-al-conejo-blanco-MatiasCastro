#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
using namespace sf;

Texture texture;
Sprite cirlce1;
Sprite cirlce2;
Sprite cirlce3;
Sprite cirlce4;

int main() {
	int width = 800;
	int height = 600;
	Sprite objects[4];
	int ObjectSelected;
	bool isPressed=false;
	objects[0]= cirlce1;
	objects[1] = cirlce2;
	objects[2] = cirlce3;
	objects[3] = cirlce4;
	texture.loadFromFile("rcircle.png");
	int index = 0;
	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j < 2; j++)
		{
			objects[index].setTexture(texture);
			objects[index].setOrigin(objects[index].getLocalBounds().width/2, objects[index].getLocalBounds().height/2);
			objects[index].setPosition(width * i, height * j);
			index++;
		}
	}
	sf::RenderWindow App(sf::VideoMode(width, height, 32),
		"Sniper");
	while (App.isOpen())
	{
		App.clear();
		Event event;
		while (App.pollEvent(event)) {
			if (event.type == Event::Closed)
				App.close();
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					Vector2i mousePos = Mouse::getPosition(App);
					for (int i = 0; i < 4; i++) {
						objects[i].setPosition(objects[i].getPosition());
						FloatRect bounds = objects[i].getGlobalBounds();
						if (bounds.contains((float)(mousePos.x), (float)(mousePos.y))) {
							ObjectSelected = i;
							isPressed = true;
						}
					}
				}
			}
			if (event.type == Event::MouseButtonReleased) {
				if (event.mouseButton.button == Mouse::Left) {
					isPressed = false;
				}
			}
		}
		Vector2i localPosition = Mouse::getPosition(App);
		if (isPressed)
		{
			objects[ObjectSelected] .setPosition(localPosition.x, localPosition.y);
		}
		for (int i = 0; i < 4; i++) {
			App.draw(objects[i]);
		}
		App.display();
	}
	return 0;
}
























/*
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>

Texture textureNew;
Texture textureCenter;
Sprite circleNew;
int main() {
	textureNew.loadFromFile("rcircle.png");
	circleNew.setTexture(textureNew);
	int width = 800;
	int height = 600;
	int objectsPosition[4][2];
	int index = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			objectsPosition[index][0] = width * i;
			objectsPosition[index][1] = height * j;
			index++;
		}
	}
	sf::RenderWindow App(sf::VideoMode(800, 600, 600),
		"Sniper");
	while (App.isOpen())
	{
		
		Event event;
		while (App.pollEvent(event)) {
			if (event.type == Event::Closed)
				App.close();
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					Vector2i mousePos = Mouse::getPosition(App);
					for (int i = 0; i < 4; i++) {
						circleNew.setPosition(static_cast<float>(objectsPosition[i][0]), static_cast<float>(objectsPosition[i][1]));
						FloatRect bounds = circleNew.getGlobalBounds();
						if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
							std::cout << "C�rculo " << i << " fue clickeado!" << std::endl;
						}
					}
				}
			}
		}
		index = 0;
		App.clear();
		for (int i = 0; i < 4; i++) {
			circleNew.setPosition(static_cast<float>(objectsPosition[i][0]), static_cast<float>(objectsPosition[i][1]));
			App.draw(circleNew);
		}
		App.draw(circleNew);
		App.display();
	}
	return 0;
}
*/