#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include "Maze.h"
#include <array>

class Character : public sf::Drawable, public sf::Transformable
{
public:
	Character();

	virtual void update(sf::Time delta);
	void setDirection(sf::Vector2i direction);
	sf::Vector2i getDirection() const;
	void setMaze(Maze* maze);

	void setSpeed(float speed);
	float getSpeed() const;

	bool willMove() const;

	sf::FloatRect getCollisionBox() const;

protected:
	virtual void changeDirection() {};

private:
	float m_speed;
	Maze* m_maze;

	sf::Vector2i m_currentDirection;
	sf::Vector2i m_nextDirection;

	sf::Vector2i m_previousIntersection;
	std::array<bool, 4> m_availableDirections;
};

#endif 