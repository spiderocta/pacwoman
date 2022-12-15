#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
class Game
{
public:
	Game();

	//run method contains the  whole game loop logic 
	void run();

	//actual game semulation methods 
	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i directon);

private:
	sf::RenderWindow window;
};

#endif GAME_H