#include <SFML/Graphics.hpp>

#include "mainMenu.h"

int menu();
int main()
{
    mainMenu print;
    print.Hello();
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
    int status=1;
    status = menu();
    sf::RenderWindow window(sf::VideoMode(1920, 1088), "TestWindow", sf::Style::Close);
    while (window.isOpen() && status == 1) {
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

int menu() {
    sf::RenderWindow menu(sf::VideoMode(1920, 1088), "Menu", sf::Style::Close);
    sf::RectangleShape play(sf::Vector2f(400.0f, 200.0f));
    play.setFillColor(sf::Color::Green);
    play.setOrigin(200, 100);
    sf::RectangleShape exis(sf::Vector2f(400.0f, 200.0f));
    exis.setFillColor(sf::Color::Red);
    exis.setOrigin(200, 100);
    

    sf::Texture background;
    sf::Event close;
    while (menu.isOpen()) {
        menu.clear();
        play.setPosition(1920/2,200);
        exis.setPosition(1920 / 2, 500);
        menu.draw(play);
        menu.draw(exis);
        menu.display();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(menu);
            if (mousePos.x > (960 - 200) && mousePos.y > (200 - 100) && mousePos.x < (960 + 200) && mousePos.y <(200 + 100)) {
                printf("Play");
                return 1;
                break;
            }
            if (mousePos.x > (960 - 200) && mousePos.y > (500 - 100) && mousePos.x < (960 + 200) && mousePos.y < (500 + 100)) {
                printf("Exis");
                return 0;
                menu.close();
                break;
            }
        }
        while (menu.pollEvent(close)) {
            if (close.type == close.Closed) {
                menu.close();
                return 0;
            }

        }
    }
}

int calMousePos() {


}