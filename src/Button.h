#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>
#include "Toolbox.h"


class Button {
public:
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);

    sf::Vector2f getPosition();

    sf::Sprite* getSprite();


    void setSprite(sf::Sprite* _sprite);

    void onClick();


private:
    sf::Vector2f position;
    std::function<void(void)> onClickCallback;
    sf::Sprite* sprite;
};

#endif
