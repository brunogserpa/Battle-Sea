#include "Player.h"
#include <iostream>

void Player::initVariables()
{
	this->dir = UP;
	this->direction.x = 0.f;
	this->direction.y = -1.f;
	this->speed = 2.f;
	this->life = 0;
	this->width = 59;
	this->height = 44;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
}

bool Player::alive()
{
	return (this->life > 0);
}

void Player::initShape()
{
	this->nTexture.loadFromFile("Assets/Sprites/Player1.png");
	this->dTexture.loadFromFile("Assets/Sprites/Player1_Damage.png");
	this->sprite.setTexture(this->nTexture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, this->width, this->height));
}

Player::Player()
	: Submarine()		//CHANGE COORDINATES
{
	this->initVariables();
	this->direction_x = true;
	this->initShape();
}

void Player::setPosition(const sf::RenderTarget* target)
{
	this->sprite.setPosition(static_cast<float>(target->getSize().x) / 2.f + 150.f, static_cast<float>(target->getSize().y) - this->sprite.getGlobalBounds().height - 15.f);
}

void Player::Damage()
{
	this->life -= 1;
	if (this->life == 1)
		this->sprite.setTexture(this->dTexture);

	if (this->life == 0)
		this->sprite.setPosition(-500.f, -500.f);
}

void Player::Heal()
{
	this->life = 2;
}

void Player::animate(float mCurrentFrame)
{
	if (this->direction_x)
		this->sprite.setTextureRect(sf::IntRect(0 + this->width * static_cast<int>(mCurrentFrame), this->height * this->dir, this->width, this->height));
	else this->sprite.setTextureRect(sf::IntRect(this->width + this->width * static_cast<int>(mCurrentFrame), this->height * this->dir, -this->width, this->height));
}

void Player::updateInput()
{
	//Keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->direction_x = false;
		this->dir = HORIZONTAL;
		this->direction.x = -1.f;
		this->direction.y = 0.f;
		this->sprite.move(this->speed * this->direction);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->direction_x = true;
		this->dir = HORIZONTAL;
		this->direction.x = 1.f;
		this->direction.y = 0.f;
		this->sprite.move(this->speed * this->direction);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->dir = UP;
		this->direction.x = 0.f;
		this->direction.y = -1.f;
		this->sprite.move(this->speed * this->direction);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->dir = DOWN;
		this->direction.x = 0.f;
		this->direction.y = 1.f;
		this->sprite.move(this->speed * this->direction);
	}
}

void Player::update(const sf::RenderTarget* target, float mCurrentFrame)
{	
	this->animate(mCurrentFrame);
	this->updateAttackCooldown();
	this->updateInput();
	this->updateWindowsBoundsCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
	this->sprite.setColor(sf::Color(static_cast<sf::Uint8>(255 - 150 * this->getBounds().top / 768), static_cast<sf::Uint8>(255 - 150 * this->getBounds().top / 768), static_cast<sf::Uint8>(255 - 150 * this->getBounds().top / 768)));
	target->draw(this->sprite);
}