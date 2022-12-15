#include "Game.h"
#include <iostream>

Game::Game() 
	:window(sf::VideoMode(640, 480), "pacwoman")
{
}

void Game::run() {

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::I) {
                    insertCoin();
                }
                if (event.key.code == sf::Keyboard::S) {
                    pressButton();
                }
                if (event.key.code == sf::Keyboard::Left) {
                    moveStick(sf::Vector2i(-1, 0));
                }
                if (event.key.code == sf::Keyboard::Right) {
                    moveStick(sf::Vector2i(1, 0));
                }
                if (event.key.code == sf::Keyboard::Down) {
                    moveStick(sf::Vector2i(0, 1));
                }
                if (event.key.code == sf::Keyboard::Up) {
                    moveStick(sf::Vector2i(0 , -1));
                }
            }

        }

        window.clear();
        //draw
        window.display();
    }
}

void Game::insertCoin()
{
    std::cout << "insert Coin" << std::endl;
}

void Game::pressButton()
{
    std::cout << "press Button" << std::endl;
}

void Game::moveStick(sf::Vector2i directon)
{
    std::cout << "move Stick" << std::endl;
}
