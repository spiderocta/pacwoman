#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "PacWoman.h"
#include "Ghost.h"
#include "Maze.h"

class Game;

class GameState {
public:

	GameState(Game* game);
	Game* getGame() const;

	enum State {
		NoCoin,
		GetReady,
		Playing,
		Won,
		Lost,
		Count
	};

	virtual void insertCoin() =0;
	virtual void pressButton() = 0;
	virtual void moveStick(sf::Vector2i directon) = 0;
	virtual void update(sf::Time delta) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

private :
	Game* game;
};


class NoCoinState : public GameState {
public:
	NoCoinState(Game* game);
	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i directon);
	void update(sf::Time delta);
	void draw(sf::RenderWindow& window);


private :
	sf::Text text;
	sf::Sprite sprite;
	bool displayText;
};



class GetReadyState : public GameState
{
public:

	GetReadyState(Game* game);

	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i direction);
	void update(sf::Time Delta);
	void draw(sf::RenderWindow& window);

private:
	sf::Text text;

};


class PlayingState : public GameState
{
public:

	PlayingState(Game* game);
	~PlayingState();

	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i direction);
	void update(sf::Time delta);
	void draw(sf::RenderWindow& window);
	void moveCharactersToInitialPosition();
	void updateCameraPosition();

	void loadNextLevel();
	void resetToZero();
	void resetCurrentLevel();
	void resetLiveCount();

private :
	PacWoman* pacwoman;
	std::vector<Ghost*> ghosts;
	//Ghost ghost;
	Maze maze;
	sf::View camera;
	sf::RenderTexture scene;

	sf::Text scoreText;
	sf::Text levelText;
	sf::Text remainingDotsText;
	sf::Sprite liveSprite[3];

	int level;
	int liveCount;
	int score;
};


class WonState : public GameState
{
public:

	WonState(Game* game);

	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i direction);
	void update(sf::Time delta);
	void draw(sf::RenderWindow& window);

private:
	sf::Text text;
};


class LostState : public GameState
{
public:

	LostState(Game* game);

	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i direction);
	void update(sf::Time delta);
	void draw(sf::RenderWindow& window);

private :
	sf::Text text;
	sf::Time countDown;
	sf::Text countDownText;
};

#endif GAMESTATE_H
