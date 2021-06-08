#ifndef GAME_H
#define GAME_H 

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include<SFML\Graphics.hpp>
#include<SFML\System.hpp>
#include<SFML\Window.hpp>
#include<SFML\Audio.hpp>
#include<SFML\Network.hpp>
/*
	Class that acts as a Game Engine
*/
class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;
	
	//Mouse Positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	
	//Resouces
	sf::Texture enemy0Texture;
	sf::Texture enemy1Texture;
	sf::Texture enemy2Texture;
	sf::Texture enemy3Texture;
	sf::Texture targetTexture;
	sf::Texture aimTexture;
	sf::Font font;
	
	//Sounds
	sf::Music bgMusic;
	sf::SoundBuffer deathSoundBuffer;
	sf::SoundBuffer shotSoundBuffer;
	sf::Sound deathSound;
	sf::Sound shotSound;
	
	//Texts
	sf::Text uiText;
	sf::Text healthText;
	sf::Text pause;
	sf::Text dead;
	sf::Text help;
	
	//Game Logic
	bool endGame;
	unsigned points;
	unsigned health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;
	bool escapePressed;
	
	//Game Objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
	sf::RectangleShape healthBar;
	sf::RectangleShape target;
	sf::RectangleShape aim;
	
	//Private Functions
	void initVariables();
	void initSounds();
	void initWindow();
	void initFonts();
	void initTexts();
	void initTextures();
	void initEnemies();
	void initComponents();
	
public:
	//Constructors and Destructors
	Game();
	virtual ~Game();
	
	//Access
	const bool running() const;
	const bool getEndGame() const;
	
	//Functions
	void spawnEnemy();
	
	void pollEvents();
	void updateMousePositions();
	void updateText();
	void updateEnemies();
	void updateHealthBar();
	void update();
	
	void renderText();//sf::RenderTarget& target);
	void renderEnemies();//sf::RenderTarget& target);
	void render();
};

#endif
