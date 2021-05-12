#pragma once

#include "Submarine.h"

/*
	Classe do player 1, com herança da classe Submarine 
	herdando seu método e formato
*/
class Player : public Submarine
{
private:
	void initShape();

protected:
	void initVariables();
	int life;
public:
//construtor
	Player();
	virtual void setPosition(const sf::RenderTarget* target);

	void Damage(); //atualiza o estado do dano sofrido pelo player
	void Heal(); //player tem duas "vidas"
	bool alive(); // retorna se o player1 está vivo 
	void animate(float mCurrentFrame); //animação 
	virtual void updateInput(); //lê os comandos do teclado
	void update(const sf::RenderTarget* target, float mCurrentFrame);
	void render(sf::RenderTarget* target);
};

