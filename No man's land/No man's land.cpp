#include <SFML/Graphics.hpp>

#include "mainMenu.h"


int main()
{
    mainMenu print;
    print.Hello();
    sf::RenderWindow window(sf::VideoMode(1920, 1088), "TestWindow" ,sf::Style::Close);
    sf::RectangleShape back(sf::Vector2f(1920.0f, 1088.0f));
    sf::RectangleShape unit1(sf::Vector2f(20.0f, 20.0f));
    sf::Texture background, unitrifleman1;

    unitrifleman1.loadFromFile("pic/rifleman.png");
    unit1.setTexture(&unitrifleman1);
    //////////////////////////////////
    sf::Sprite unit1sp;
    unit1sp.setTexture(unitrifleman1);
    unit1sp.setTextureRect(sf::IntRect(220, 20, 400, 400));
    /////////////////////////////
    background.loadFromFile("pic/background.png");
    back.setTexture(&background);
    unit1sp.setScale(sf::Vector2f(0.5f, .5f));

    while (window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            unit1sp.setScale(sf::Vector2f(0.5f, .5f));
            unit1sp.move(.5f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            unit1sp.setScale(sf::Vector2f(-0.5f, .5f));
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

void map() {
    sf::RenderWindow window(sf::VideoMode(1920, 1088), "TestWindow", sf::Style::Close);
    sf::RectangleShape back(sf::Vector2f(1920.0f, 1088.0f));
    sf::Texture background;
    background.loadFromFile("pic/background.png");
    back.setTexture(&background);
    window.clear();
    window.draw(back);
    window.display();
}