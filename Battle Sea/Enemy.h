#pragma once

#include "Submarine.h"
#include <random>

/*
	Classe de herança da classe Submarine,
	configura textura e animação dos submarinos inimigos.
*/
class Enemy : public Submarine
{
private:
	std::default_random_engine engine;
	void initShape(sf::Texture& texture); //inicializa textura
	int randDirection; //variável para setar direções randomicas para cada inimigo
	sf::Int64 timeBeforeMoving;
	sf::Int64 timeBeforeShot;

protected:
	void initVariables(float spawnSide); //inicializa as variaveis de direção e posição

public:
	//construtor com parametros de textura, posição x (posição y todos iniciam com a mesma) e direção
	Enemy(sf::Texture& texture, float x_, float spawnSide);

	void move(const sf::Int64& time); //movimentação dos inimigos
	void animate(float mCurrentFrame); //animação
	void update(sf::RenderTarget* target, float mCurrentFrame, const sf::Int64& time); //atualização da movimentação
	void render(sf::RenderTarget* target); //renderização das texturas
};

