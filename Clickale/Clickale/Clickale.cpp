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

class Crosshair {
private:
	sf::Sprite sprite;
	sf::Texture texture;

public:
	Crosshair(const std::string& texturePath) {
		if (!texture.loadFromFile(texturePath)) {
			// Handle error
		}
		sprite.setTexture(texture);
		sprite.setScale(0.5f, 0.5f);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	}

	void updatePosition(const sf::Vector2i& mousePosition) {
		sprite.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
	}

	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}
};
class Enemy {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	static constexpr float SCALE = 0.1f;

public:
	Enemy(const sf::Texture& texture, float x, float y) : sprite(texture) {
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		sprite.setPosition(x, y);
		sprite.setScale(SCALE, SCALE);
	}

	const sf::Sprite& getSprite() const {
		return sprite;
	}

	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}
};

class EnemyManager {
private:
	std::list<Enemy> enemies;
	sf::Texture texture;

public:
	EnemyManager(const std::string& texturePath) {
		if (!texture.loadFromFile(texturePath)) {
			// Handle error
		}
	}

	void createEnemies(int enemyAmount, int width, int height) {
		for (int i = 0; i < enemyAmount; ++i) {
			float randomX = static_cast<float>(rand() % width);
			float randomY = static_cast<float>(rand() % height);
			enemies.emplace_back(texture, randomX, randomY);
		}
	}

	void drawEnemies(sf::RenderWindow& window) {
		for (Enemy& enemy : enemies) {
			enemy.draw(window);
		}
	}

	void checkHits(const sf::Vector2i& mousePosition) {
		auto it = enemies.begin();
		while (it != enemies.end()) {
			if (it->getSprite().getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
				it = enemies.erase(it);
			}
			else {
				++it;
			}
		}
	}

	bool isEmpty() const {
		return enemies.empty();
	}
};

int main() {
	int width = 1000;
	int height = 800;
	sf::RenderWindow App(sf::VideoMode(width, height, 32), "Sniper");

	Crosshair crosshair("crosshair.png");
	EnemyManager enemyManager("et.png");
	int enemyAmount = 5;
	enemyManager.createEnemies(enemyAmount, width, height);

	while (App.isOpen()) {
		App.clear();
		App.setMouseCursorVisible(false);
		sf::Event event;
		while (App.pollEvent(event)) {
			// ...
		}

		sf::Vector2i mousePos = sf::Mouse::getPosition(App);

		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				enemyManager.checkHits(mousePos);
			}
		}

		enemyManager.drawEnemies(App);
		if (enemyManager.isEmpty()) {
			enemyManager.createEnemies(enemyAmount, width, height);
		}

		crosshair.updatePosition(mousePos);
		crosshair.draw(App);
		App.display();
	}
	return 0;
}
