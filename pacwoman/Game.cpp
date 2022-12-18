#include "Game.h"
#include <iostream>

Game::Game() 
	:window(sf::VideoMode(640, 480), "pacwoman")
{
    if (!font.loadFromFile("assets/font.ttf")) {
        throw std::runtime_error("unable to load font from 'assets/font.ttf'");
    }

    if (!logo.loadFromFile("assets/logo.png")) {
        throw std::runtime_error("unable to load logo 'assets/logo.png'");
    }

    if (!texture.loadFromFile("assets/texture.png")) {
        throw std::runtime_error("unable to load texture from 'assets/texture.png'");
    }


    gameStates[GameState::NoCoin] = new NoCoinState(this);
    gameStates[GameState::GetReady] = new GetReadyState(this);
    gameStates[GameState::Playing] = new PlayingState(this);
    gameStates[GameState::Won] = new WonState(this);
    gameStates[GameState::Lost] = new LostState(this);

    //the initial game state
    changeGameState(GameState::NoCoin);
}

Game::~Game()
{
    for (GameState* gameState : gameStates) {
        delete gameState;
    }
}



void Game::run() {

    sf::Clock frameClock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::I) {
                    currentState->insertCoin();
                }
                if (event.key.code == sf::Keyboard::S) {
                    currentState->pressButton();
                }
                if (event.key.code == sf::Keyboard::Left) {
                    currentState->moveStick(sf::Vector2i(-1, 0));
                }
                if (event.key.code == sf::Keyboard::Right) {
                    currentState->moveStick(sf::Vector2i(1, 0));
                }
                if (event.key.code == sf::Keyboard::Down) {
                    currentState->moveStick(sf::Vector2i(0, 1));
                }
                if (event.key.code == sf::Keyboard::Up) {
                    currentState->moveStick(sf::Vector2i(0 , -1));
                }
            }

        }

        currentState->update(frameClock.restart());
        window.clear();
        currentState->draw(window);
        window.display();
    }
}

sf::Font& Game::getFont()
{
    return font;
}

sf::Texture& Game::getLogo()
{
    return logo;
}

sf::Texture& Game::getTexture()
{
    return texture;
}

void Game::changeGameState(GameState::State gameState)
{
    currentState = gameStates[gameState];
}
