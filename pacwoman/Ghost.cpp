#include "Ghost.h"

Ghost::Ghost(sf::Texture& texture)
    :visual(texture)
    , isWeak(false)
    , weaknessDuration(sf::Time::Zero)
    //,pacWoman(pacWoman)
{
    setOrigin(20, 20);

}

void Ghost::setWeak(sf::Time duration)
{
	isWeak = true;
	weaknessDuration = duration;
}


bool Ghost::isWeak() const
{
	return isWeak;
}

void Ghost::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(visual, states);
}