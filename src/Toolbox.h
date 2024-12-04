#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Button.h"


class Button;

class Toolbox {
public:
    sf::RenderWindow window;
    GameState* gameState;

    Button* debugButton;
    Button* newGameButton;
    Button* testButton1;
    Button* testButton2;
    Button* testButton3;

    static Toolbox& getInstance();

	bool debugMode;

private:
    Toolbox();
	~Toolbox();
    static Toolbox* instance;

    sf::Texture debugTexture;
    sf::Texture newGameTexture;
    sf::Texture testButton1Texture;
    sf::Texture testButton2Texture;
    sf::Texture testButton3Texture;


    sf::Sprite debugSprite;
    sf::Sprite newGameSprite;
    sf::Sprite testButton1Sprite;
    sf::Sprite testButton2Sprite;
    sf::Sprite testButton3Sprite; 
};

#endif
