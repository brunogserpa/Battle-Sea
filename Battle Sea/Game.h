#pragma once

#include<ctime>
#include<vector>
#include<sstream>
#include<map>

#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Screen.h"
#include "Player.h"
#include "Player2.h"
#include "Enemy.h"
#include "Missile.h"

/*
	Principal classe do jogo, contém toda a principal lógica 
	de funcionamento e inicialização das principais variáveis.
*/
class Game
{
private:
	std::default_random_engine engine; //para o uso de numeros randomicos

	//varáveis da janela
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//variáveis para fontes/mensagens
	sf::Font font;
	sf::Text uiText;

	//variáveis da lógica do jogo
	bool game_paused;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	unsigned int maxEnemies;
	unsigned int p1_score;
	unsigned int p2_score;
	float mCurrentFrame;
	float timeBeforeShooting;

	//Objetos do jogo

	//jogadores
	Player player1;
	Player2 player2;
	enum SubmarineType { P1, P2, ENEMY };
	//texturas
	std::map<std::string, sf::Texture*> textures;
	sf::Texture enemyTexture;
	std::vector<Enemy*> enemies;
	sf::Texture missileTexture;
	//misseis
	std::vector<Missile*> p1_missiles;
	std::vector<Missile*> p2_missiles;
	std::vector<Missile*> enemy_missiles;

	//sprites
	sf::Sprite background;
	sf::Sprite sand;
	sf::Sprite plants;

	Screen screen;

	//inicialização de variáveis
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initTextures();
	void initEnemies();
	void initGame();

public:
	//variáveis de estado de jogo
	bool gameStarted;
	bool endGame;
	bool twoPlayers;

	//Constructors and Destructors
	Game();
	virtual ~Game();

	//Accessors
	bool running() const;			//Check if Window is open

	//Funções do funcionamento do jogo
	void spawnEnemies();

	void pollEvents();

	void updateText();
	void updateEnemies(float mCurrentFrame, const sf::Int64& time);
	void updateMissiles(std::vector<Missile*>& missiles);
	void updateCombat(std::vector<Missile*>& missiles, SubmarineType type);

	void updateP1Collision();
	void updateP2Collision();
	void updateEnemiesCollision();

	void updateGame(const sf::Int64& time);
	void update();

	//renderização das imagens do jogo	
	void renderText();
	void renderEnemies();
	void renderMissiles(const std::vector<Missile*>& missiles);
	void renderGame();
	void render();
};

