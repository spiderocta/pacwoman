#ifndef PACWOMAN_GHOST_H
#define PACWOMAN_GHOST_H

#include "Animator.h"
#include "PacWoman.h" 
#include "Character.h"

class Ghost : public Character
{
public:

	enum State
	{
		Strong,
		Weak
	};

public:
	Ghost(sf::Texture& texture, PacWoman* pacWoman);

	void setWeak(sf::Time duration);
	bool isWeak() const;

	void update(sf::Time delta);

protected:
	void changeDirection();


private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool m_isWeak;
	sf::Time m_weaknessDuration;

	sf::Sprite m_visual;
	PacWoman* m_pacWoman;

	Animator m_strongAnimator;
	Animator m_weakAnimator;
};

#endif