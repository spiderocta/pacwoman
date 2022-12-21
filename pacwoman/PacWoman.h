#ifndef PACWOMAN_H
#define PACWOMAN_H

#include "Character.h"

class PacWoman : public Character
{
private:
	sf::Sprite visual;
	bool isDying;
	bool isDead;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	PacWoman(sf::Texture& texture);
	void die();

	bool isDying() const;
	bool isDead() const;


};

#endif