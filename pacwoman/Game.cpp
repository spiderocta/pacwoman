#include "Game.h"
#include <iostream>

Game::Game() 
	:window(sf::VideoMode(640, 480), "pacwoman")
{
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

        currentState->update(sf::seconds(1));
        window.clear();
        currentState->draw(window);
        window.display();
    }
}

void Game::changeGameState(GameState::State gameState)
{
    currentState = gameStates[gameState];
}
