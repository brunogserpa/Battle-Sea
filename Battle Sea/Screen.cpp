#include "Screen.h"
#include <iostream>


void Screen::initVariables()
{
    this->screens["MENU"] = new sf::Texture();
    this->screens["MENU"]->loadFromFile("Assets/Images/Menu.png");
    this->screens["INSTRUCTIONS"] = new sf::Texture();
    this->screens["INSTRUCTIONS"]->loadFromFile("Assets/Images/Instructions.png");
    this->screens["GAMEOVER"] = new sf::Texture();
    this->screens["GAMEOVER"]->loadFromFile("Assets/Images/GameOver.png");

    this->mSprite.setTexture(*this->screens["MENU"]);
    
    this->select = 0;
    this->currentScreen = MENU;
}

void Screen::initSelectSprite()
{
    this->mTexture.loadFromFile("Assets/Sprites/Player1.png");
    this->selectSprite.setTexture(this->mTexture);
    this->selectSprite.setTextureRect(sf::IntRect(0, 0, 59, 44));
    this->selectSprite.setPosition(400, 379);
}

Screen::Screen()
{
    this->initVariables();
    this->initSelectSprite();
}

Screen::~Screen()
{
    for (auto& i : this->screens)
    {
        delete i.second;
    }
}

void Screen::initFont(sf::Font& font)
{
    this->mStr.setFont(font);
    this->mStr.setPosition(465, 379);
    this->mStr.setCharacterSize(70);
    this->mStr.setString("1 PLAYER\n2 PLAYERS\nINSTRUCTIONS");
}

void Screen::setScreen(int screen)
{
    switch (screen)
    {
    case 0:
        this->currentScreen = MENU;
        this->mSprite.setTexture(*this->screens["MENU"]);
        break;
    case 1:
        this->currentScreen = INSTRUCTIONS;
        this->mSprite.setTexture(*this->screens["INSTRUCTIONS"]);
        break;
    case 2:
        this->currentScreen = GAMEOVER;
        this->mSprite.setTexture(*this->screens["GAMEOVER"]);
        break;
    default:
        break;
    }
}

int Screen::updateScreen(sf::Window* target)
{
    while (target->pollEvent(this->ev))
    {
        if (this->ev.type == sf::Event::Closed)
            target->close();
        else if (this->ev.type == sf::Event::KeyPressed)
        {
            if (this->currentScreen == MENU)
            {
                if (this->ev.key.code == sf::Keyboard::Down)
                {
                    if (this->select < 2)
                    {
                        this->select++;
                        this->selectSprite.setPosition(400.f, 379.f + static_cast<float>(this->select) * 100.f);
                    }
                }
                if (this->ev.key.code == sf::Keyboard::Up)
                {
                    if (this->select > 0)
                    {
                        this->select--;
                        this->selectSprite.setPosition(400.f, 379.f + static_cast<float>(this->select) * 100.f);
                    }
                }
                if (this->ev.key.code == sf::Keyboard::Escape)
                {
                    //this->setScreen(0);
                    target->close();
                }
                if (this->ev.key.code == sf::Keyboard::Enter)
                {
                    if (this->select == 0)
                    {
                        return 1;
                    }
                    else if (this->select == 1)
                    {
                        return 2;
                    }
                    else if (this->select == 2)
                    {
                        this->setScreen(1);
                    }
                }
            }
            else
            {
                if (this->ev.key.code == sf::Keyboard::Escape)
                {
                    this->setScreen(0);
                }
            }
        }
    }
    return 0;
}

void Screen::renderScreen(sf::RenderTarget* target)
{
    target->clear();

    target->draw(this->mSprite);
    if (this->currentScreen == MENU)
    {
        target->draw(this->mStr);
        target->draw(this->selectSprite);
    }
}
