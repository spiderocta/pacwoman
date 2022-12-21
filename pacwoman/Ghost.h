#ifndef PACWOMAN_GHOST_H
#define PACWOMAN_GHOST_H

#include "Character.h"
#include "PacWoman.h"

class Ghost : public Character
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite visual;
	bool isWeak;
	sf::Time weaknessDuration;
	PacWoman* m_pacWoman;

public:
	enum State
	{
		Strong,
		Weak
	};

	Ghost(sf::Texture& texture);

	void setWeak(sf::Time duration);
	bool isWeak() const;
};

#endif