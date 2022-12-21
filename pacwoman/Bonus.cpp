#include "Bonus.h"

void Bonus::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(visual, states);
}

Bonus::Bonus(sf::Texture& texture)
	: visual(texture)
{
	setFruit(Banana);
	visual.setOrigin(15, 15);
}


void Bonus::setFruit(Fruit fruit)
{
	//slicing from the spritesheet
	if (fruit == Banana)
		visual.setTextureRect(sf::IntRect(32, 0, 30, 30));
	else if (fruit == Apple)
		visual.setTextureRect(sf::IntRect(32 + 30, 0, 30, 30));
	else if (fruit == Cherry)
		visual.setTextureRect(sf::IntRect(32 + 60, 0, 30, 30));
}