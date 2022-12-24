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
	sprite.setPosition(40, 50);

	text.setFont(game->getFont());
	text.setString("Please Insert A Coin");
	
	//center text 
	centerOrigin(text);
	text.setPosition(270, 150);

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
	text.setString("Press start when you are ready"); 
	text.setCharacterSize(15);

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
{
	//pacwoamn.move(100, 100);
	//ghost.move(200, 200);
	maze.loadLevel("large-level");
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
	
}

void PlayingState::draw(sf::RenderWindow& window)
{
	window.setView(camera);
	window.draw(maze);
	window.draw(*pacwoman);

	for (Ghost* ghost : ghosts)
		window.draw(*ghost);
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
