#include "Dot.h"

sf::CircleShape Dot::getDot()
{   
    sf::CircleShape dot;
    dot.setRadius(4);
    dot.setFillColor(sf::Color::White);
    dot.setOrigin(2, 2);

    return dot;
}

sf::CircleShape Dot::getSuperDot()
{
    sf::CircleShape superDot;
    superDot.setRadius(8);
    superDot.setFillColor(sf::Color::White);
    superDot.setOrigin(4, 4);

    return superDot;
}
