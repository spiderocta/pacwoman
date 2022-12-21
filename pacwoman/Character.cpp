#include "Character.h"

Character::Character()
	:speed(1.f)
{
}

void Character::setSpeed(float speed)
{
	speed = speed;
}

float Character::getSpeed() const
{
	return speed;
}
