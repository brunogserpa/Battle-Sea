#include <iostream>
#include "Game.h"

void Game::initVariables()
{
	this->window = nullptr;

	this->gameStarted = false;
	this->twoPlayers = false;
	this->endGame = false;
	this->enemyTexture.loadFromFile("Assets/Sprites/Enemy.png");
}

void Game::initWindow()
{
	this->videoMode.height = 768;
	this->videoMode.width = 1366;
	this->videoMode.bitsPerPixel = 32;
	this->window = new sf::RenderWindow(this->videoMode, "Battle Sea", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);

	sf::Image icon;
	icon.loadFromFile("Assets/Sprites/Icon.png");
	this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Assets/Fonts/cherry.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << std::endl;
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(40);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
}

void Game::initTextures()
{
	this->textures["BACKGROUND"] = new sf::Texture();
	this->textures["BACKGROUND"]->loadFromFile("Assets/Images/Background.png");
	this->textures["BACKGROUND"]->setRepeated(true);
	this->background.setTexture(*this->textures["BACKGROUND"]);

	this->textures["SAND"] = new sf::Texture();
	this->textures["SAND"]->loadFromFile("Assets/Sprites/Sand.png");
	this->textures["SAND"]->setRepeated(true);
	this->sand.setTexture(*this->textures["SAND"]);
	this->sand.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->window->getSize().x), 15));
	this->sand.setPosition(0.f, static_cast<float>(this->window->getSize().y) - 15.f);

	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Assets/Sprites/Missile.png");

	this->textures["PLANTS"] = new sf::Texture();
	this->textures["PLANTS"]->loadFromFile("Assets/Sprites/Plants2.png");
	this->textures["PLANTS"]->setRepeated(true);
	this->plants.setTexture(*this->textures["PLANTS"]);
	this->plants.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->window->getSize().x), 70));
	this->plants.setPosition(0.f, static_cast<float>(this->window->getSize().y) - 70.f);
}

void Game::initGame()
{
	this->enemySpawnTimerMax = 100.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 20;
	this->p1_score = 0;
	this->p2_score = 0;
	this->player1.setPosition(this->window);
	this->player1.Heal();
	if (this->twoPlayers)
	{
		this->player2.setPosition(this->window);
		this->player2.Heal();
	}
}

//Constructors and Destructors

Game::Game() : engine{ static_cast<unsigned int>(time(0)) }
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initTextures();

	sf::Clock clock;
	this->screen.initFont(this->font);

	while (this->running()) {
		//Game loop
		this->window->setKeyRepeatEnabled(false);
		while (!this->gameStarted && this->running())
		{
			this->update();
			this->render();
		}

		this->window->setKeyRepeatEnabled(true);
		this->initGame();

		while (this->gameStarted && this->running())
		{
			this->pollEvents();
			if (!this->game_paused)
			{
				sf::Int64 time = clock.getElapsedTime().asMicroseconds();
				clock.restart();
				time /= 800;
				this->updateGame(time);
			}
			this->render();
		}
	}
}

Game::~Game()
{
	for (auto& i : this->textures)
	{
		delete i.second;
	}
	for (auto* i : this->enemies)
		delete i;
	for (auto *i : this->p1_missiles)
		delete i;
	for (auto *i : this->p2_missiles)
		delete i;
	for (auto *i : this->enemy_missiles)
		delete i;

	delete this->window;
}

bool Game::running() const
{
	return this->window->isOpen();
}

//Functions

void Game::spawnEnemies()
{
	/*
		Spawns enemies and sets their position
	*/
	std::uniform_int_distribution<unsigned int> randEnemyPosition(0, static_cast<unsigned int>(this->window->getSize().x) - static_cast<unsigned int>(50.f));
	this->enemies.push_back(new Enemy(this->enemyTexture, static_cast<float>(randEnemyPosition(engine)), 1.f));
}

void Game::pollEvents()
{
	//Event pooling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->screen.setScreen(2);
				this->gameStarted = false;
			}
			break;
		default:
			break;
		}
	}
}

void Game::updateText()
{
	std::stringstream ss;

	if (twoPlayers)
		ss << "Score\nP1: " << this->p1_score << "\nP2: " << this->p2_score;
	else ss << "Score: " << this->p1_score;
	this->uiText.setString(ss.str());
}

void Game::updateEnemies(float CurrentFrame, const sf::Int64& time)
{
	/*
		-Check number of enemies spawned
		-Check enemy timer
			-Spawn enemies and reset enemy timer
			or
			-Increase enemy timer
	*/
	//std::cout << time << std::endl;
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemies();
			//Check if enemy was spawned on top of another enemy
			for (size_t i = 0; i < this->enemies.size() - 1; i++)
			{
				if (this->enemies[this->enemies.size() - 1]->getBounds().intersects(this->enemies[i]->getBounds()))
				{
					delete this->enemies[this->enemies.size() - 1];
					this->enemies.erase(this->enemies.begin() + static_cast<long int>(this->enemies.size()) - 1);
				}
			}
			this->enemySpawnTimer = 0.f;
		}
		else
			//Update the timer for enemy spawning
			this->enemySpawnTimer += 1.f;
	}

	//Move the enemies
	for (auto& e : this->enemies)
	{
		e->update(this->window, CurrentFrame, time);
	}
}

void Game::updateMissiles(std::vector<Missile*>& missiles)
{
	unsigned counter = 0;
	for (auto* missile : missiles)
	{
		missile->update();

		if ((missile->getBounds().left <= 0.f) || (missile->getBounds().left + missile->getBounds().width >= static_cast<float>(this->window->getSize().x)) ||
			(missile->getBounds().top <= 0.f) || (missile->getBounds().top + missile->getBounds().height >= static_cast<float>(this->window->getSize().y) - this->plants.getGlobalBounds().height))
		{
			delete missiles.at(counter);
			missiles.erase(missiles.begin() + counter);
			--counter;
		}
		++counter;
	}
}

void Game::updateCombat(std::vector<Missile*>& missiles, SubmarineType type)
{
	for (size_t k = 0; k < missiles.size(); k++)
	{
		bool hit = false;
		for (size_t i = 0; i < this->enemies.size() && hit == false; i++)
		{
			if (this->enemies[i]->getBounds().intersects(missiles[k]->getBounds()))
			{
				if (type != ENEMY)
				{
					delete this->enemies[i];
					this->enemies.erase(this->enemies.begin() + static_cast<long int>(i));
				}
				delete missiles[k];
				missiles.erase(missiles.begin() + static_cast<long int>(k));

				hit = true;
				
				if (type == P1)
					this->p1_score++;
				else if (type == P2)
					this->p2_score++;
			}
		}
		if (!hit) 
		{
			if (this->player1.getBounds().intersects(missiles[k]->getBounds()))
			{
				this->player1.Damage();

				delete missiles[k];
				missiles.erase(missiles.begin() + static_cast<long int>(k));
			}
			else if (this->twoPlayers) {
				if (this->player2.getBounds().intersects(missiles[k]->getBounds()))
				{
					this->player2.Damage();

					delete missiles[k];
					missiles.erase(missiles.begin() + static_cast<long int>(k));
				}
			}
		}
	}
}

void Game::updateP1Collision()
{
	if (this->twoPlayers)
	{
		if (this->player1.getBounds().intersects(this->player2.getBounds()))
		{
			this->player1.collisionMovement();
		}
		else
		{
			for (size_t i = 0; i < this->enemies.size(); i++)
			{
				if (this->player1.getBounds().intersects(this->enemies[i]->getBounds()))
				{
					this->player1.collisionMovement();
				}
			}
		}
	}
	else
	{
		for (size_t i = 0; i < this->enemies.size(); i++)
		{
			if (this->player1.getBounds().intersects(this->enemies[i]->getBounds()))
			{
				this->player1.collisionMovement();
			}
		}
	}
}

void Game::updateP2Collision()
{
	if (this->player2.getBounds().intersects(this->player1.getBounds()))
	{
		this->player2.collisionMovement();
	}
	else 
	{
		for (size_t i = 0; i < this->enemies.size(); i++)
		{
			if (this->player2.getBounds().intersects(this->enemies[i]->getBounds()))
			{
				this->player2.collisionMovement();
			}
		}
	}
}

void Game::updateEnemiesCollision()
{
	for (size_t k = 0; k < this->enemies.size(); k++)
	{
		if (this->player1.getBounds().intersects(this->enemies[k]->getBounds()))
		{
			this->enemies[k]->collisionMovement();
		}
		if (this->twoPlayers)
		{
			if (this->player2.getBounds().intersects(this->enemies[k]->getBounds()))
			{
				this->enemies[k]->collisionMovement();
			}
			else
			{
				for (size_t i = 0; i < this->enemies.size(); i++)
				{
					if (i != k && this->enemies[i]->getBounds().intersects(this->enemies[k]->getBounds()))
					{
						this->enemies[k]->collisionMovement();
					}
				}
			}
		}
		else
		{
			for (size_t i = 0; i < this->enemies.size(); i++)
			{
				if (i != k && this->enemies[i]->getBounds().intersects(this->enemies[k]->getBounds()))
				{
					this->enemies[k]->collisionMovement();
				}
			}
		}
	}
}

void Game::updateGame(const sf::Int64& timee)
{
	this->mCurrentFrame += 0.005f * static_cast<float>(timee);

	if (this->mCurrentFrame >= 2)
		this->mCurrentFrame -= 2;
	if (!this->endGame)
	{
		this->updateText();
		if (this->player1.alive())
		{
			this->player1.update(this->window, this->mCurrentFrame);
			this->updateP1Collision();
		}
		if (this->twoPlayers)
		{
			if (this->player2.alive())
			{
				this->player2.update(this->window, this->mCurrentFrame);
				this->updateP2Collision();
			}
		}
		this->updateEnemies(this->mCurrentFrame, timee);
		this->updateEnemiesCollision();
		this->updateMissiles(this->p1_missiles);
		if (this->twoPlayers)
			this->updateMissiles(this->p2_missiles);
		this->updateMissiles(this->enemy_missiles);
		this->updateCombat(this->p1_missiles, P1);
		if (this->twoPlayers)
			this->updateCombat(this->p2_missiles, P2);
		this->updateCombat(this->enemy_missiles, ENEMY);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player1.canAttack())
		{
			this->p1_missiles.push_back(new Missile(this->textures["BULLET"], 
				this->player1.getPosition().x, this->player1.getPosition().y, this->player1.getDirection(), this->player1.getPointedDirection()));
		}
		if (this->twoPlayers)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && this->player2.canAttack())
			{
				this->p2_missiles.push_back(new Missile(this->textures["BULLET"],
					this->player2.getPosition().x, this->player2.getPosition().y, this->player2.getDirection(), this->player2.getPointedDirection()));
			}
		}
		//Random Enemy Shooting Logic
		this->timeBeforeShooting += static_cast<float>(timee);
		
		//std::default_random_engine engine{static_cast<unsigned int>(time(0))};
		std::uniform_int_distribution<unsigned int> randEnemyShooting(0,500);
		if (this->timeBeforeShooting > static_cast<float>(3000 / (this->enemies.size()+1) + randEnemyShooting(engine)))
		{
			size_t i = static_cast<long unsigned int>(this->timeBeforeShooting) % this->enemies.size();
			this->timeBeforeShooting = 0.f;
			this->enemy_missiles.push_back(new Missile(this->textures["BULLET"],
				this->enemies[i]->getPosition().x, this->enemies[i]->getPosition().y, this->enemies[i]->getDirection(), this->enemies[i]->getPointedDirection()));
		}
	}
	if (!this->player1.alive() && !this->player2.alive()) {
		this->screen.setScreen(2);
		this->gameStarted = false;
	}
}

void Game::update()
{
	int action = this->screen.updateScreen(this->window);
	if (action == 1)
	{
		this->twoPlayers = false;
		this->gameStarted = true;
	}
	if (action == 2)
	{
		this->twoPlayers = true;
		this->gameStarted = true;
	}
}

void Game::renderText()
{
	this->window->draw(this->uiText);
}

void Game::renderEnemies()
{
	for (auto& e : this->enemies)
	{
		e->render(this->window);
	}
}

void Game::renderMissiles(const std::vector<Missile*>& missiles)
{
	for (auto *missile : missiles)
		missile->render(this->window);
}

void Game::renderGame()
{	
	/*
		Render the game objects

		-clear old frame
		-render objects
		-display new frame
	*/

	this->window->clear(sf::Color::Cyan);
	this->window->draw(this->background);
	this->window->draw(this->sand);

	//Draw game

	if (this->player1.alive())
		this->player1.render(this->window);
	if (this->player2.alive())
		this->player2.render(this->window);

	this->renderEnemies();

	this->renderMissiles(p1_missiles);
	this->renderMissiles(p2_missiles);
	this->renderMissiles(enemy_missiles);

	this->window->draw(this->plants);
	this->renderText();
}

void Game::render()
{
	if (this->gameStarted)
		this->renderGame();
	else
		this->screen.renderScreen(this->window);

	this->window->display();
}