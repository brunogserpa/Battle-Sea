#include "Submarine.h"

void Submarine::updateAttackCooldown()
{
    if (this->attackCooldown < this->attackCooldownMax)
        this->attackCooldown += 0.5f;
}

bool Submarine::canAttack()
{
    if (this->attackCooldown >= this->attackCooldownMax) 
    {
        this->attackCooldown = 0.f;
        return true;
    }
    return false;
}

const sf::Vector2f& Submarine::getPosition() const
{
    return this->sprite.getPosition();
}

const sf::Vector2f& Submarine::getDirection()
{
    return this->direction;
}

bool Submarine::getPointedDirection()
{
    return this->direction_x;
}

const sf::FloatRect Submarine::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Submarine::collisionMovement()
{
		this->sprite.move(-this->speed * this->direction);
}

void Submarine::updateWindowsBoundsCollision(const sf::RenderTarget* target)
{
	//Left
	if (this->sprite.getGlobalBounds().left <= 0.f) {
		this->sprite.setPosition(0.f, this->sprite.getGlobalBounds().top);
	}
	//Right
	if (this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width >= static_cast<float>(target->getSize().x))
		this->sprite.setPosition(static_cast<float>(target->getSize().x) - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);
	//Top
	if (this->sprite.getGlobalBounds().top <= 0.f) /*{
		this->dir = DOWN;
		this->direction.x = 0.f;
		this->direction.y = 1.1f;
	}*/
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, 0.f);
	//Bottom
	if (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= static_cast<float>(target->getSize().y) -15)
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, static_cast<float>(target->getSize().y) - this->sprite.getGlobalBounds().height - 15);
}