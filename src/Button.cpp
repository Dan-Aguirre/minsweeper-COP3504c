
#include "Button.h"
#include <SFML/Graphics.hpp>
#include "Toolbox.h"
#include "iostream"

Button::Button(sf::Vector2f _position, std::function<void(void)> _onClick): position(_position), onClickCallback(_onClick), sprite(nullptr) {}

sf::Vector2f Button::getPosition() {
    return position;
}

//returns and draws sprite
sf::Sprite* Button::getSprite() {
	if (sprite != nullptr) {
 	sprite->setPosition(position.x, position.y);
        Toolbox::getInstance().window.draw(*sprite);

}
    return sprite;
}

void Button::setSprite(sf::Sprite* _sprite) {

    sprite = _sprite;
}

//calls function for when clicked
void Button::onClick() {
	    if (onClickCallback) {
		onClickCallback();
	    }
}




