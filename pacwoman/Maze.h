#ifndef MAZE_H
#define MAZE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Maze : public sf::Drawable
{
public:

	Maze(sf::Texture& texture);
	void loadLevel(std::string name);

	sf::Vector2i getPacWomanPosition() const;
	std::vector<sf::Vector2i> getGhostPositions() const;

	inline std::size_t positionToIndex(sf::Vector2i position) const;
	inline sf::Vector2i indexToPosition(std::size_t index) const;

	sf::Vector2i mapPixelToCell(sf::Vector2f pixel) const;
	sf::Vector2f mapCellToPixel(sf::Vector2i cell) const;

	bool isWall(sf::Vector2i position) const;

	sf::Vector2i getSize() const;

private:

	enum CellData
	{
		Empty,
		Wall,
		Dot,
		SuperDot,
		Bonus
	};

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2i mazeSize;
	std::vector<CellData> mazeData;
	sf::Vector2i pacWomanPosition;
	std::vector<sf::Vector2i> ghostPositions;

	sf::RenderTexture renderTexture;
	sf::Texture& texture;
};

#endif
