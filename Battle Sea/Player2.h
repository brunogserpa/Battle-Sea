#pragma once

#include "Submarine.h"
#include "Player.h"

class Player2 : public Player
{
private:
	virtual void initShape();

public:
	Player2();
	virtual ~Player2();
	void setPosition(const sf::RenderTarget* target) override;
	void updateInput() override;
};