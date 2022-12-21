#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SFML/Graphics.hpp>

class Animator
{
public:
    Animator();

    void addFrame(sf::IntRect frame);

    void play(sf::Time duration, bool loop);
    bool isPlaying() const;

    void update(sf::Time delta);
    void animate(sf::Sprite& sprite);

private:
    std::vector<sf::IntRect> m_frames;

    bool m_isPlaying;
    sf::Time m_duration;
    bool m_loop;

    unsigned int m_currentFrame;
};


#endif