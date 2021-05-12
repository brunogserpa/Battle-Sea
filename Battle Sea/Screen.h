#pragma once
#include <SFML/Graphics.hpp>


enum Screens{ MENU, INSTRUCTIONS, GAMEOVER };
class Screen {
private:
    sf::Sprite mSprite;
    sf::Sprite selectSprite;
    std::map<std::string, sf::Texture*> screens;
    sf::Event ev;

    sf::Text mStr;
    sf::Texture mTexture;
    int select;
    Screens currentScreen;

    void initVariables();
    void initSelectSprite();

public:
    Screen();
    virtual ~Screen();

    void initFont(sf::Font& font);
    void setScreen(int screen);
    int updateScreen(sf::Window* target);
    void renderScreen(sf::RenderTarget* target);
};
