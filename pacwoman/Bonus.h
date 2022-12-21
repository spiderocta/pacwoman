#ifndef BONUS_H
#define BONUS_H

#include <SFML/Graphics.hpp>

class Bonus : public sf::Drawable, public sf::Transformable
{
private:
	sf::Sprite visual;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	enum Fruit
	{
		Banana,
		Apple,
		Cherry
	};

	Bonus(sf::Texture& texture);
	void setFruit(Fruit fruit);
};

#endif BONUS_H