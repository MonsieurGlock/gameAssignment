#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1088), "TestWindow", sf::Style::Close);
    sf::RectangleShape back(sf::Vector2f(1920.0f, 1088.0f));
    sf::RectangleShape unit1(sf::Vector2f(20.0f, 20.0f));
    sf::Texture background, unitrifleman1;

    unitrifleman1.loadFromFile("pic/rifleman.png");
    unit1.setTexture(&unitrifleman1);
    //////////////////////////////////
    sf::Sprite unit1sp;
    unit1sp.setTexture(unitrifleman1);
    unit1sp.setTextureRect(sf::IntRect(200, 20, 610, 400));
    /////////////////////////////
    background.loadFromFile("pic/background.png");
    back.setTexture(&background);
    

    while (window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            unit1sp.move(.5f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            unit1sp.move(-.5f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            unit1sp.move(0.f, 0.5f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            unit1sp.move(0.f, -0.5f);
        }
        sf::Event cat;
        while (window.pollEvent(cat)) {
            if (cat.type == cat.Closed) {
                window.close();
            }

        }
        window.clear();
        window.draw(back);
        window.draw(unit1sp);
        window.display();
    }

    return 0;
}