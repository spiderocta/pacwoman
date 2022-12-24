#ifndef PACWOMAN_H
#define PACWOMAN_H

#include "Character.h"
#include "Animator.h"

class PacWoman : public Character
{
public:
	PacWoman(sf::Texture& texture);
	void die();

	bool isDying() const;
	bool isDead() const;

	void update(sf::Time delta);
	void reset();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool m_isDying;
	bool m_isDead;
	sf::Sprite m_visual;

	Animator m_runAnimator;
	Animator m_dieAnimator;
};

#endif