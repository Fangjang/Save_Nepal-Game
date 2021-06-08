#include "game.h"
#define PRACHANDA "./Textures/prachanda.png"
#define KP "./Textures/kp.png"
#define BIDYA "./Textures/bidya.png"
#define DEUBA "./Textures/deuba.png"

//Private Functions
void Game::initVariables()
{
	this->window = NULL;
	
	//Game Logic
	endGame = false;
	//window->setMouseCursorVisible(false);
	this->points = 0;
	this->health = 10;
	this->enemySpawnTimerMax = 30.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHeld = false;
	this->escapePressed = false;
	this->aim.setSize(sf::Vector2f(50.f,50.f));
	this->aim.setOrigin(25.f,25.f);
	this->aim.setPosition(400.f,250.f);
}

void Game::initSounds()
{
	//Set Sounds
	this->bgMusic.openFromFile("./Sounds/kaha_janchau.ogg");
	this->bgMusic.setLoop(true);
	this->bgMusic.play();
	
	this->deathSoundBuffer.loadFromFile("./Sounds/dead.ogg");
	this->shotSoundBuffer.loadFromFile("./Sounds/shot.ogg");
	
	this->deathSound.setBuffer(deathSoundBuffer);
	this->shotSound.setBuffer(shotSoundBuffer);
}

void Game::initWindow()
{
	this->videomode.height = 500;
	this->videomode.width = 800;
	this->window = new sf::RenderWindow(this->videomode, "Save Nepal'", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	this->font.loadFromFile("./Fonts/Plaguard.otf");
}

void Game::initTexts()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(18);
	this->uiText.setPosition(10.f,31.f);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
	
	this->healthText.setFont(this->font);
	this->healthText.setCharacterSize(18);
	this->healthText.setPosition(10.f,10.f);
	this->healthText.setString("Health");
	
	this->pause.setFont(this->font);
	this->pause.setCharacterSize(18);
	this->pause.setPosition(200,250);
	this->pause.setString("Game Paused\nPress Esc to keep Playing\nPress X to Exit");
	
	this->dead.setFont(this->font);
	this->dead.setCharacterSize(18);
	this->dead.setPosition(200,230);
	this->dead.setFillColor(sf::Color::Red);
	this->dead.setString("You are dead");
	
	this->help.setFont(this->font);
	this->help.setCharacterSize(18);
	this->help.setPosition(330.f, 60.f);
	this->help.setFillColor(sf::Color::Red);
	this->help.setString("SAVE NEPAL");
}

void Game::initTextures()
{
	this->enemy0Texture.loadFromFile(PRACHANDA);
	this->enemy1Texture.loadFromFile(KP);
	this->enemy2Texture.loadFromFile(BIDYA);
	this->enemy3Texture.loadFromFile(DEUBA);
	this->targetTexture.loadFromFile("./Textures/nepal.png");
	this->aimTexture.loadFromFile("./Textures/aim.png");
	this->target.setTexture(&(this->targetTexture));
	this->aim.setTexture(&(this->aimTexture));
}

void Game::initEnemies()
{
	
	this->enemy.setPosition(10.f,10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f,0.5f));
//	this->enemy.setFillColor(sf::Color::Cyan);
//	this->enemy.setOutlineColor(sf::Color::Green);
//	this->enemy.setOutlineThickness(5.f);
}

void Game::initComponents()
{
	this->healthBar.setPosition(80.f,10.f);
	this->healthBar.setSize(sf::Vector2f(static_cast<float>(health * 20),20.f));
	this->healthBar.setFillColor(sf::Color::Green);
	this->healthBar.setOutlineColor(sf::Color::White);
	this->healthBar.setOutlineThickness(3.f);
	
	this->target.setPosition(350.f, 10.f);
	this->target.setSize(sf::Vector2f(50.f,50.f));
	this->target.setOutlineColor(sf::Color::Green);
	this->target.setOutlineThickness(3.f);
}

//Constructors and Destructors
Game::Game()
{
	this->initVariables();
	this->initSounds();
	this->initWindow();
	this->initFonts();
	this->initTexts();
	this->initTextures();
	this->initEnemies();
	this->initComponents();
}

Game::~Game()
{
	delete this->window;
}

//Access
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

//Functions
void Game::spawnEnemy()
{
	/*
		Spawns the enemies and sets their color and position
		-Sets a random postion
		-Sets a random color
		-Adds enemy to the vector
	*/
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);
	
	int enemyTextureRand = rand() % 4;
	
	switch(enemyTextureRand)
	{
		case 0:
			this->enemy.setTexture(&(this->enemy0Texture));
			break;
		case 1:
			this->enemy.setTexture(&(this->enemy1Texture));
			break;
		case 2:
			this->enemy.setTexture(&(this->enemy2Texture));
			break;
		case 3:
			this->enemy.setTexture(&(this->enemy3Texture));
			break;
	}
	
//	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::Cyan);
	this->enemy.setOutlineThickness(5.f);
	
	this->enemies.push_back(this->enemy);
}

void Game::pollEvents()
{
	while(this->window->pollEvent(this->ev))
	{
		switch(this->ev.type)
		case sf::Event::Closed:
			this->window->close();
			break;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		if(escapePressed == false)
		{
			escapePressed = true;
			if(this->getEndGame() == false)
			{	
				this->endGame = true;
			}
			else
			{
				this->endGame = false;
			}
		}
	}
	else
	{
		escapePressed = false;
	}
	if(this->endGame == true)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			this->window->close();
		}
	}
	
	if(health <= 0)
	{
		this->endGame = true;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			this->endGame = false;
			if(health <= 0)
			{
				this->health = 10;
				this->points = 0;
			}
		}
	}
}

void Game::updateMousePositions()
{
	//Update mouse Position relative to current instance window
	//Update aim position
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
	this->aim.setPosition(mousePosWindow.x, mousePosWindow.y);
}

void Game::updateText()
{
	std::stringstream ss;
	
	ss << "Points: " << this->points;
	
	this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{
	/*
		Updates the enemy spawn timer and spawns the enemies
		when the total number of enemies is smaller than max number of enemies
		Moves the enemies downwards
		Removes the enemy at the edge of the screen //TODO
	*/
	//updating the timer for enemy spawning
	if(this->enemies.size() < this->maxEnemies)
	{
		if(this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Resets the timer and spawns the enemy
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}
	
	//Moving and deleting enemeis outside the screen
	for(int i = 0; i < this->enemies.size(); i++)
	{	
		//Move enemies downward
		this->enemies[i].move(0.f,5.f);
		
		//Delete the enemies outside the screen
		if(this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			if(health >= 1)
			{
				this->health -= 1;
			}
		}
	}
	
	//Check if the enemies are clicked upon
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->shotSound.play();
		if(mouseHeld == false)
		{
			mouseHeld = true;
			bool deleted =  false;
			for(int i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if(this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					this->deathSound.play();
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
					//Increase Points
					this->points += 1;
				}	
			}
		}
	}
	else
		this->mouseHeld = false;
}

void Game::updateHealthBar()
{
	//Update the health Bar Graphics
	this->healthBar.setSize(sf::Vector2f(static_cast<float>(this->health)* 20,20.f));
	if(this->health <= 4)
	{
		this->healthBar.setFillColor(sf::Color::Red);
	}
	else
		this->healthBar.setFillColor(sf::Color::Green);
}

void Game::update()
{
	this->pollEvents();
		
	if(this->endGame == false)
	{
		this->updateMousePositions();
		this->updateText();
		this->updateEnemies();
		this->updateHealthBar();
	}
		
}

void Game::renderText()
{
	this->window->draw(this->uiText);
	this->window->draw(this->healthText);
	this->window->draw(this->help);
	if(this->endGame == true)
	{
		if(health <= 0)
		{
			this->window->draw(this->dead);
		}
		this->window->draw(this->pause);
	}
}

void Game::renderEnemies()
{
	//Remdering all the enemies
	for(auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Game::render()
{
	/*
		-clear old frame
		-render objects
		-display game objects
	*/
	this->window->clear();
	
	//Draw Game Objets
	//this->window->draw(this->enemy);
	this->window->draw(this->healthBar);
	this->window->draw(this->target);
	this->window->draw(this->aim);
	this->renderEnemies();
	
	this->renderText();
	this->window->display();
}
