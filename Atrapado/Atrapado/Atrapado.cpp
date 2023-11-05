#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
using namespace std;
using namespace sf;
Texture circleTexture;
Texture squareTexture;
Sprite object;
float width = 800;
float height = 600;
bool CheckBounds(Vector2f toMovePosition, Vector2f direction, Vector2f objectSize)
{
    if ((toMovePosition.x + direction.x + objectSize.x) > width || (toMovePosition.y + direction.y + objectSize.x) > height)
        return false;
    if ((toMovePosition.x + direction.x) <  0 || (toMovePosition.y + direction.y) < 0)
        return false;
    return true;
}

void AdjustSpriteToSize(Sprite& sprite, const Texture& texture, float desiredWidth, float desiredHeight) {
    Vector2u textureSize = texture.getSize();
    float scaleX = desiredWidth / textureSize.x;
    float scaleY = desiredHeight / textureSize.y;
    sprite.setScale(scaleX, scaleY);
}

void Move(Sprite& toMove, Vector2f direction) {
    Vector2u textureSize = toMove.getTexture()->getSize();
    if (CheckBounds(toMove.getPosition(), direction, Vector2f(textureSize.x*toMove.getScale().x, textureSize.y * toMove.getScale().y)))
    {
        Vector2f position = toMove.getPosition();
        toMove.setPosition(position + direction); 
    }
}
int main()
{
    
    float speed = 0.1;
    circleTexture.loadFromFile("rcircle.png");
    squareTexture.loadFromFile("cuad_yellow.png");
    object.setTexture(squareTexture);
    object.setPosition(width / 2, height / 2);
    sf::RenderWindow App(sf::VideoMode(width, height, 32),
        "Sniper");
    float desiredWidth = 100.0f; 
    float desiredHeight = 100.0f; 
    AdjustSpriteToSize(object, squareTexture, desiredWidth, desiredHeight);
    int index = 1;
    list<Texture> textures;
    textures.push_back(circleTexture);
    textures.push_back(squareTexture);
    while (App.isOpen())
    {
        App.clear();
        Event event;
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            Move(object, Vector2f(-1 * speed, 0 * speed));
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            Move(object, Vector2f(1 * speed, 0 * speed));
        }
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            Move(object, Vector2f(0 * speed, -1 * speed));
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            Move(object, Vector2f(0 * speed, 1 * speed));
        }
        while (App.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) 
            {
                if (event.key.code == sf::Keyboard::Space) 
                {
                    index = (index + 1) % textures.size();
                    std::list<Texture>::iterator it = textures.begin();
                    std::advance(it, index);
                    object.setTexture(*it);
                    AdjustSpriteToSize(object, *it, desiredWidth, desiredHeight);
                }
            }
        }
        App.draw(object);
        App.display();
    }
}
