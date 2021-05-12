#include "Player2.h"

void Player2::initShape()
{
	//this->shape.setFillColor(sf::Color::Black);
	//this->shape.setSize(sf::Vector2f(60.f, 60.f));
	this->nTexture.loadFromFile("Assets/Sprites/Player2.png");
	this->dTexture.loadFromFile("Assets/Sprites/Player2_Damage.png");
	this->sprite.setTexture(this->nTexture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, this->width, this->height));
}

Player2::Player2()
	: Player()		//CHANGE COORDINATES
{
	this->initVariables();
	this->direction_x = false;
	this->initShape();
}

Player2::~Player2()
{
}

void Player2::setPosition(const sf::RenderTarget* target)
{
	this->sprite.setPosition(static_cast<float>(target->getSize().x) / 2.f - 150.f, 
	static_cast<float>(target->getSize().y) - this->sprite.getGlobalBounds().height -15.f);
}

void Player2::updateInput()
{
	//Keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->direction_x = false;
		this->dir = HORIZONTAL;
		this->direction.x = -1.f;
		this->direction.y = 0.f;
		this->sprite.move(this->speed * this->direction);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->direction_x = true;
		this->dir = HORIZONTAL;
		this->direction.x = 1.f;
		this->direction.y = 0.f;
		this->sprite.move(this->speed * this->direction);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->dir = UP;
		this->direction.x = 0.f;
		this->direction.y = -1.f;
		this->sprite.move(this->speed * this->direction);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->dir = DOWN;
		this->direction.x = 0.f;
		this->direction.y = 1.f;
		this->sprite.move(this->speed * this->direction);
	}
}