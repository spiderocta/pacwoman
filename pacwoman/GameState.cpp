#include "GameState.h"
#include "Game.h"

//utility 
template <typename T>
void centerOrigin(T& drawable) {
	sf::FloatRect bound = drawable.getLocalBounds();
	drawable.setOrigin(bound.width /2, bound.height / 2);
}


GameState::GameState(Game* game)
	: game(game)
{

}

Game* GameState::getGame() const
{
	return game;
}


//no coin state 

NoCoinState::NoCoinState(Game* game)
	:GameState(game)
{
	//initializations
	sprite.setTexture(game->getLogo());
	sprite.setPosition(20, 50);

	text.setFont(game->getFont());
	text.setString("Insert A Coin");
	
	//center text 
	centerOrigin(text);
	text.setPosition(240, 180);

	displayText = true;
}

void NoCoinState::insertCoin()
{
	getGame()->changeGameState(GameState::GetReady);
}

void NoCoinState::pressButton()
{
}

void NoCoinState::moveStick(sf::Vector2i directon)
{
}

void NoCoinState::update(sf::Time delta)
{
	//blinking logic
	static sf::Time timeBuffer = sf::Time::Zero;
	timeBuffer = timeBuffer + delta;

	while (timeBuffer >= sf::seconds(0.5)) {
		displayText = !displayText;
		timeBuffer = timeBuffer - sf::seconds(1);
	}
}

void NoCoinState::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	if (displayText) {
		window.draw(text);
	}
}


// get ready state
GetReadyState::GetReadyState(Game* game)
	:GameState(game)
{
	text.setFont(game->getFont());
	text.setString("Press Start when you're ready...");
	text.setCharacterSize(14);

	centerOrigin(text);
	text.setPosition(240, 240);
}

void GetReadyState::insertCoin()
{
}

void GetReadyState::pressButton()
{ 
	getGame()->changeGameState(GameState::Playing);
}

void GetReadyState::moveStick(sf::Vector2i direction)
{ 
	//testing 
	if (direction.x == -1) {
		getGame()->changeGameState(GameState::Lost);
	}
	else if (direction.x == 1)
	{
		getGame()->changeGameState(GameState::Won);
	}
	
}

void GetReadyState::update(sf::Time delta)
{
}

void GetReadyState::draw(sf::RenderWindow& window)
{ 
	window.draw(text);
}


//playing state
PlayingState::PlayingState(Game* game)
	:GameState(game)
	//, pacwoamn(game->getTexture())
	//, ghost(game->getTexture())
	,maze(game->getTexture())
	,pacwoman(nullptr)
	, level(0)
	, liveCount(3)
	, score(0)
{
	//pacwoamn.move(100, 100);
	//ghost.move(200, 200);
	maze.loadLevel("medium");
	pacwoman = new PacWoman(game->getTexture());
	pacwoman->setMaze(&maze);
	pacwoman->setPosition(maze.mapCellToPixel(maze.getPacWomanPosition()));

	//iterating over ghosts 
	for (sf::Vector2i ghostPosition : maze.getGhostPositions())
	{
		Ghost* ghost = new Ghost(game->getTexture(), pacwoman);
		ghost->setMaze(&maze);
		ghost->setPosition(maze.mapCellToPixel(ghostPosition));

		ghosts.push_back(ghost);
	}
	camera.setSize(sf::Vector2f(480, 480));
	scene.create(480, 480);

	scoreText.setFont(game->getFont());
	scoreText.setCharacterSize(10);
	scoreText.setPosition(10, 480);
	scoreText.setString("0 points");

	levelText.setFont(game->getFont());
	levelText.setCharacterSize(10);
	levelText.setPosition(160, 480);
	levelText.setString("level x");

	remainingDotsText.setFont(game->getFont());
	remainingDotsText.setCharacterSize(10);
	remainingDotsText.setPosition(280, 480);
	remainingDotsText.setString("0 dots");

	for (auto& liveSprite : liveSprite)
	{
		liveSprite.setTexture(game->getTexture());
		liveSprite.setTextureRect(sf::IntRect(122, 0, 20, 20));
	}

	liveSprite[0].setPosition(sf::Vector2f(415, 480));
	liveSprite[1].setPosition(sf::Vector2f(435, 480));
	liveSprite[2].setPosition(sf::Vector2f(455, 480));
}

void PlayingState::insertCoin()
{
	//pacwoman->die();
}

void PlayingState::pressButton()
{
	//ghost.setWeak(sf::seconds(3));
}

void PlayingState::moveStick(sf::Vector2i direction)
{
	pacwoman->setDirection(direction);
}

void PlayingState::update(sf::Time delta)
{
	camera.setCenter(pacwoman->getPosition());

	if (camera.getCenter().x < 240)
		camera.setCenter(240, camera.getCenter().y);
	if (camera.getCenter().y < 240)
		camera.setCenter(camera.getCenter().x, 240);

	if (camera.getCenter().x > maze.getSize().x * 32 - 240)
		camera.setCenter(maze.getSize().x * 32 - 240, camera.getCenter().y);

	if (camera.getCenter().y > maze.getSize().y * 32 - 240)
		camera.setCenter(camera.getCenter().x, maze.getSize().y * 32 - 240);

	pacwoman->update(delta);

	for (Ghost* ghost : ghosts) {

		ghost->update(delta);
	} 

	sf::Vector2f pixelPosition = pacwoman->getPosition();
	sf::Vector2f offset(std::fmod(pixelPosition.x, 32), std::fmod(pixelPosition.y, 32));
	offset -= sf::Vector2f(16, 16);
	
	if (offset.x <= 2 && offset.x >= -2 && offset.y <= 2 && offset.y >= -2)
	{
		sf::Vector2i cellPosition = maze.mapPixelToCell(pixelPosition);

		if (maze.isDot(cellPosition))
		{
			
		}
		else if (maze.isSuperDot(cellPosition))
		{
			for (Ghost* ghost : ghosts)
				ghost->setWeak(sf::seconds(5));

			
		}
		else if (maze.isBonus(cellPosition))
		{
			
		}

		maze.pickObject(cellPosition);
	}


	for (Ghost* ghost : ghosts)
	{
		if (ghost->getCollisionBox().intersects(pacwoman->getCollisionBox()))
		{
			if (ghost->isWeak())
			{
				ghosts.erase(std::find(ghosts.begin(), ghosts.end(), ghost));

				
			}
			else
				pacwoman->die();
		}
	}

	if (pacwoman->isDead())
	{
		pacwoman->reset();

		liveCount--;

		if (liveCount < 0)
			getGame()->changeGameState(GameState::Lost);
		else
			moveCharactersToInitialPosition();
	}


	if (maze.getRemainingDots() == 0)
	{
		getGame()->changeGameState(GameState::Won);
	}

	updateCameraPosition();

	// Update score text and remaining dots
	scoreText.setString(std::to_string(score) + " points");
	remainingDotsText.setString(std::to_string(maze.getRemainingDots()) + "x dots");
}

void PlayingState::draw(sf::RenderWindow& window)
{
	scene.clear();
	scene.setView(camera);
	scene.draw(maze);
	scene.draw(*pacwoman);

	for (Ghost* ghost : ghosts) {
		scene.draw(*ghost);
	}
	scene.display();

	window.draw(sf::Sprite(scene.getTexture()));

	window.draw(scoreText);
	window.draw(levelText);
	window.draw(remainingDotsText);

	for (unsigned int i = 0; i < liveCount; i++)
		window.draw(liveSprite[i]);
}

void PlayingState::moveCharactersToInitialPosition()
{
	pacwoman->setPosition(maze.mapCellToPixel(maze.getPacWomanPosition()));

	auto ghostPositions = maze.getGhostPositions();
	for (unsigned int i = 0; i < ghosts.size(); i++)
		ghosts[i]->setPosition(maze.mapCellToPixel(ghostPositions[i]));

	updateCameraPosition();
}

void PlayingState::updateCameraPosition()
{
	camera.setCenter(pacwoman->getPosition());

	if (camera.getCenter().x < 240)
		camera.setCenter(240, camera.getCenter().y);
	if (camera.getCenter().y < 240)
		camera.setCenter(camera.getCenter().x, 240);

	if (camera.getCenter().x > maze.getSize().x * 32 - 240)
		camera.setCenter(maze.getSize().x * 32 - 240, camera.getCenter().y);

	if (camera.getCenter().y > maze.getSize().y * 32 - 240)
		camera.setCenter(camera.getCenter().x, maze.getSize().y * 32 - 240);

}

void PlayingState::loadNextLevel()
{
	maze.loadLevel("large-level");

	level++;

	int mapLevel = level % 3;
	int speedLevel = std::floor(level / 3);

	if (mapLevel == 0)
		maze.loadLevel("small");
	else if (mapLevel == 1)
		maze.loadLevel("medium");
	else if (mapLevel == 2)
		maze.loadLevel("large");

	// Destroy previous characters
	for (Ghost* ghost : ghosts)
		delete ghost;

	ghosts.clear();

	// Create new characters
	for (auto ghostPosition : maze.getGhostPositions())
	{
		Ghost* ghost = new Ghost(getGame()->getTexture(), pacwoman);
		ghost->setMaze(&maze);
		//ghost->setPosition(m_maze.mapCellToPixel(ghostPosition));

		ghosts.push_back(ghost);
	}

	// Change speed according to the new level
	float speed = 100 + (speedLevel * 50);

	pacwoman->setSpeed(speed + 25);

	for (auto& ghost : ghosts)
		ghost->setSpeed(speed);

	moveCharactersToInitialPosition();

	//Update level text
	levelText.setString("level " + std::to_string(speedLevel) + " - " + std::to_string(mapLevel + 1));

}

void PlayingState::resetToZero()
{
	resetLiveCount();

	level = 0;
	resetCurrentLevel();

	score = 0;
}

void PlayingState::resetCurrentLevel()
{
	level--;
	loadNextLevel();
}

void PlayingState::resetLiveCount()
{
	liveCount = 3;
}

PlayingState::~PlayingState()
{
	delete pacwoman;

	for (Ghost* ghost : ghosts)
		delete ghost;
}

//won state 
WonState::WonState(Game* game)
	:GameState(game)
{ 
	text.setFont(game->getFont());
	text.setString("You Won");
	text.setCharacterSize(42);
	centerOrigin(text);
	text.setPosition(240, 120);
}

void WonState::insertCoin()
{
}

void WonState::pressButton()
{
}

void WonState::moveStick(sf::Vector2i direction)
{
}

void WonState::update(sf::Time delta)
{
	static sf::Time timeBuffer = sf::Time::Zero;
	timeBuffer = timeBuffer + delta;

	while (timeBuffer.asSeconds() > 5) {
		getGame()->changeGameState(GameState::GetReady);
	}
}

void WonState::draw(sf::RenderWindow& window)
{ 
	window.draw(text);
}


//lost state
LostState::LostState(Game* game)
	:GameState(game)
{ 
	text.setFont(game->getFont());
	text.setString("You Lost");
	text.setCharacterSize(42);
	centerOrigin(text);
	text.setPosition(240, 120);
	countDownText.setFont(game->getFont());
	countDownText.setCharacterSize(12);
	centerOrigin(countDownText);
	countDownText.setPosition(240, 240);
}

void LostState::insertCoin()
{
}

void LostState::pressButton()
{
}

void LostState::moveStick(sf::Vector2i direction)
{
}

void LostState::update(sf::Time delta)
{
	countDown += delta;
	if (countDown.asSeconds() >= 10) {
		getGame()->changeGameState(GameState::GetReady);
	}
	countDownText.setString("Insert Another Coin To Continue.... " + std::to_string(10 - static_cast<int>(countDown.asSeconds())));
}

void LostState::draw(sf::RenderWindow& window)
{
	window.draw(text);
	window.draw(countDownText);
}
