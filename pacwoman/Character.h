#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

class Character : public sf::Drawable, public sf::Transformable
{
public:
	Character();

	void setSpeed(float speed);
	float getSpeed() const;

private:
	float speed;

};

#endif 