#include "PacWoman.h"

PacWoman::PacWoman(sf::Texture& texture)
    : visual(texture)
    , isDying(false)
    , isDead(false)
{
    setOrigin(20, 20);

}

void PacWoman::die()
{
    isDead = true;
}

bool PacWoman::isDying() const
{
    return isDying;
}

bool PacWoman::isDead() const
{
    return isDead;
}

void PacWoman::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    if (!isDead)
    {
        target.draw(visual, states);
    }
        
}
