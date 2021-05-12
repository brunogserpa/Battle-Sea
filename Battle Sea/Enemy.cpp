#include "Enemy.h"

void Enemy::initVariables(float spawnSide) //-1.f for right and 1.f for left
{
	this->dir = DOWN;
    if (spawnSide > 0.f)
        this->direction_x = true;
    else this->direction_x = false;
    this->direction.x = 0.f;
    this->direction.y = 1.3f;
	this->speed = 1.f;
	this->width = 60;
	this->height = 44;
    this->timeBeforeMoving = 0;
}

void Enemy::initShape(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, this->width, this->height));
}

Enemy::Enemy(sf::Texture& texture, float x_, float spawnSide)
	: engine{ static_cast<unsigned int>(time(0)) }
{
	this->initVariables(spawnSide);
	this->initShape(texture);
	this->sprite.setPosition(x_, -46.f);
}

void Enemy::move(const sf::Int64& time)
{
    this->timeBeforeMoving += time;
    std::uniform_int_distribution<unsigned int> randTime(0, 500);
    std::uniform_int_distribution<unsigned int> randomizeDirection(0, 3);
    if (this->timeBeforeMoving > 2000 +  randTime(engine) % 501) {
        this->randDirection =  randomizeDirection(engine) % 4;
        this->timeBeforeMoving = 0;
    }

    switch (this->randDirection) {
    case 0:
        this->direction_x = false;
        this->dir = HORIZONTAL;
        this->direction.x = -1.f;
        this->direction.y = 0.f;
        break;

    case 1:
        this->direction_x = true;
        this->dir = HORIZONTAL;
        this->direction.x = 1.f;
        this->direction.y = 0.f;
        break;

    case 2:
        this->dir = UP;
        this->direction.x = 0.f;
        this->direction.y = -1.f;
        break;

    case 3:
        this->dir = DOWN;
        this->direction.x = 0.f;
        this->direction.y = 1.3f;
        break;
    default:
        break;
    }
}

void Enemy::animate(float mCurrentFrame)
{
	if (this->direction_x)
		this->sprite.setTextureRect(sf::IntRect(0 + this->width *  static_cast<int> (mCurrentFrame), this->height * this->dir, this->width, this->height));
	else this->sprite.setTextureRect(sf::IntRect(this->width + this->width *  static_cast<int> (mCurrentFrame), this->height * this->dir, -this->width, this->height));
}

void Enemy::update(sf::RenderTarget* target, float mCurrentFrame, const sf::Int64& time)
{	
	this->animate(mCurrentFrame);
    if (this->sprite.getGlobalBounds().top >= 0.f)
    {
        this->move(time);
        this->sprite.move(this->speed * this->direction);
        this->updateWindowsBoundsCollision(target);
    }
    else 
        this->sprite.move(this->speed * this->direction);
}

void Enemy::render(sf::RenderTarget* target)
{
    this->sprite.setColor(sf::Color(static_cast<uint8_t>(255 - 150 * (this->getBounds().top + 46) / 768), 
        static_cast<uint8_t>(255 - 150 * (this->getBounds().top + 46)/ 768), 
        static_cast<uint8_t>(255 - 150 * (this->getBounds().top + 46) / 768)));
	target->draw(this->sprite);
}