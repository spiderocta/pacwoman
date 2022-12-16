#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <array>
#include "GameState.h"

class Game
{

public:
	Game();

	~Game();
	//run method contains the  whole game loop logic 
	void run();

	void changeGameState(GameState::State gameState);

private:
	sf::RenderWindow window;
	GameState* currentState;
	std::array<GameState*, GameState::Count> gameStates;
};

#endif GAME_H