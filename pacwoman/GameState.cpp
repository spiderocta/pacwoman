#include "GameState.h"


GameState::GameState(Game* game)
	: game(game)
{

}

Game* GameState::getGame() const
{
	return game;
}


//no coin state 

NoCoinState::NoCoinState(Game* game)
	:GameState(game)
{

}

void NoCoinState::insertCoin()
{
}

void NoCoinState::pressButton()
{
}

void NoCoinState::moveStick(sf::Vector2i directon)
{
}

void NoCoinState::update(sf::Time delta)
{
}

void NoCoinState::draw(sf::RenderWindow& window)
{
}


// get ready state
GetReadyState::GetReadyState(Game* game)
	:GameState(game)
{
}

void GetReadyState::insertCoin()
{
}

void GetReadyState::pressButton()
{
}

void GetReadyState::moveStick(sf::Vector2i direction)
{
}

void GetReadyState::update(sf::Time Delta)
{
}

void GetReadyState::draw(sf::RenderWindow& window)
{
}


//playing state
PlayingState::PlayingState(Game* game)
	:GameState(game)
{
}

void PlayingState::insertCoin()
{
}

void PlayingState::pressButton()
{
}

void PlayingState::moveStick(sf::Vector2i direction)
{
}

void PlayingState::update(sf::Time Delta)
{
}

void PlayingState::draw(sf::RenderWindow& window)
{
}


//won state 
WonState::WonState(Game* game)
	:GameState(game)
{
}

void WonState::insertCoin()
{
}

void WonState::pressButton()
{
}

void WonState::moveStick(sf::Vector2i direction)
{
}

void WonState::update(sf::Time Delta)
{
}

void WonState::draw(sf::RenderWindow& window)
{
}


//lost state
LostState::LostState(Game* game)
	:GameState(game)
{
}

void LostState::insertCoin()
{
}

void LostState::pressButton()
{
}

void LostState::moveStick(sf::Vector2i direction)
{
}

void LostState::update(sf::Time Delta)
{
}

void LostState::draw(sf::RenderWindow& window)
{
}
