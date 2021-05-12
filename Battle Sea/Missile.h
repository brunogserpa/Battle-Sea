#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


/*
	Classe das balas/misseis usados no jogo
*/
class Missile
{
private:
	void initVariables(); //inicializa as variaveis

	sf::Vector2f direction;
protected:

	//variáveis de posição;
	float x;
	float y;
	int height;
	int width;

	float speed; //velocidade

public:

	sf::Sprite sprite;
	//construtor
	Missile(sf::Texture* texture, float pos_x, float pos_y, sf::Vector2f direction, bool pointed_x);

	void initSprite(sf::Texture* texture); //textura
	void update();
	void render(sf::RenderTarget* target);
	const sf::FloatRect getBounds() const;
};

