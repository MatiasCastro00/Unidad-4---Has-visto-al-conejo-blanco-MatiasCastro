#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow App(sf::VideoMode(200, 200, 32),
        "Sniper");

    while (App.isOpen()) {
        sf::Event event;
        while (App.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                App.close();

            if (event.type == sf::Event::Resized) {
                int newWidth = event.size.width;
                int newHeight = event.size.height;

                if (newWidth < 100) newWidth = 100;
                if (newHeight < 100) newHeight = 100;
                if (newWidth > 1000) newWidth = 300;
                if (newHeight > 1000) newHeight = 1000;

                App.setSize(sf::Vector2u(newWidth, newHeight));
            }
        }

        App.clear();
        App.display();
    }

    return 0;
}
