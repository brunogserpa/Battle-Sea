#include "Missile.h"
#include<iostream>

void Missile::initVariables()
{
	//this->dir = UP;  //CHANGE
	this->speed = 10.f;
	this->width = 11;
	this->height = 4;
}

void Missile::initSprite(sf::Texture * texture)
{
	this->sprite.setTexture(*texture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, this->width, this->height));
}

Missile::Missile(sf::Texture * texture, float pos_x, float pos_y, sf::Vector2f dir_sub, bool pointed_x)
{
	this->initVariables();
	this->initSprite(texture);
	this->sprite.setOrigin(static_cast<float>(this->width)/2, static_cast<float>(this->height)/2);
	this->direction = dir_sub;
	if (this->direction.x > 0.f)
	{
		//pos_x += 46.f + this->width/2;
		pos_x += 60.f + static_cast<float>(this->width)/2;
		pos_y += 30.f + static_cast<float>(this->height)/2;
	}
	else if (this->direction.x < 0.f)
	{
		this->sprite.setRotation(180.f);
		//pos_x += 13.f - this->width/2;
		pos_x -= 1.f + static_cast<float>(this->width)/2;
		pos_y += 30.f + static_cast<float>(this->height)/2;
	}
	else if (this->direction.y > 0.f)
	{
		this->sprite.setRotation(90.f);
		if (pointed_x)
			pos_x += 32.f + static_cast<float>(this->height)/2;
		else pos_x += 23.f + static_cast<float>(this->height)/2;
		pos_y += 45.f + static_cast<float>(this->width)/2;
	}
	else
	{
		this->sprite.setRotation(270.f);
		if (pointed_x)
			pos_x += 32.f + static_cast<float>(this->height)/2;
		else pos_x += 23.f + static_cast<float>(this->height)/2;
		//pos_y += 20.f - this->width/2;
		pos_y -= (1.f + static_cast<float>(this->width)/2);
	}
	this->sprite.setPosition(pos_x, pos_y);
}

void Missile::update()
{
	this->sprite.move(this->speed * this->direction);
}

void Missile::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

const sf::FloatRect Missile::getBounds() const
{
	return this->sprite.getGlobalBounds();
}
