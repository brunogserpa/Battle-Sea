#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
/*
	Classe Base para os submarinos inimigos e players
	seta os parâmetros de texturas e posição
	e os principais métodos para a verificação de colisão entre
	todos os submarinos e seu funcionamento
*/
class Submarine
{
protected:

	sf::Texture nTexture;	//textura quando o submarino é novo
	sf::Texture dTexture;	//textura do submarino com danos

	enum Direction { UP, HORIZONTAL, DOWN };

	//Position
	
	Direction dir;
	sf::Vector2f direction;
	bool direction_x;
	float x;
	float y;
	int height;
	int width;

	float speed;

	float attackCooldown;
	float attackCooldownMax;

public:
	
	sf::Sprite sprite;

	void updateAttackCooldown();
	bool canAttack();
	const sf::Vector2f& getPosition() const;
	const sf::Vector2f& getDirection();
	bool getPointedDirection();
	const sf::FloatRect getBounds() const;
	void collisionMovement();
	void updateWindowsBoundsCollision(const sf::RenderTarget* target);
};

