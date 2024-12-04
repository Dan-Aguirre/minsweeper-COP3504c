#include "Tile.h"
#include "Toolbox.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Tile::Tile(sf::Vector2f position): position(position), currentState(HIDDEN), isMine(false) {
neighbors.fill(nullptr);
	//neighbors = getNeighbors();

}


sf::Vector2f Tile::getLocation() {
    return position;
}


Tile::State Tile::getState() {
    return currentState;
}


//find surroinding tiles
std::array<Tile*, 8>& Tile::getNeighbors() {
    static std::array<Tile*, 8> _neighbors;
    _neighbors.fill(nullptr);

    int x = position.x / 32;
    int y = position.y / 32;
    
    int i = 0;
    for (int sy = -1; sy <= 1; sy++) {
        for (int sx = -1; sx <= 1; sx++) {
            if (sy == 0 && sx == 0) continue;

            int nx = x + sx, ny = y + sy;

            if (nx >= 0 && nx < 25 && ny >= 0 && ny < 16) {
                
                if (i < 8) {
                    _neighbors[i] = Toolbox::getInstance().gameState->getTile(nx,ny);
                    i++;
                } else {
                    break; 
                }
            }
        }
        if (i >= 8) break;
    }
    return _neighbors;
}

void Tile::setState(State _state) {
    currentState = _state;

}


void Tile::setNeighbors(std::array<Tile*, 8> _neighbors) {
    neighbors = _neighbors;
}

//manage left click & lose condition (click on bomb)
void Tile::onClickLeft() {
	if(Toolbox::getInstance().gameState->getPlayStatus() == GameState::PLAYING){
    if (currentState != FLAGGED){
    if (isMine){
        Toolbox::getInstance().gameState->setPlayStatus(GameState::LOSS);
        setState(EXPLODED);


        for (int y = 0; y < 16; y++) {
            for (int x = 0; x < 25; x++) {
                Tile& _ttile = *Toolbox::getInstance().gameState->getTile(x,y);
                   	if (_ttile.isMine) {
                    _ttile.setState(Tile::EXPLODED);
}}}


                sf::Texture* newGameTexture = new sf::Texture(); 
                sf::Sprite* newGameSprite = new sf::Sprite();  


                if (!newGameTexture->loadFromFile("./P4-data/images/face_lose.png")) {
                    std::cout << "Error loading new game image" << std::endl;
                } else {
                    newGameSprite->setTexture(*newGameTexture); 
                }

                Toolbox::getInstance().newGameButton->setSprite(newGameSprite);


    }else{
        setState(REVEALED);
	neighbors = getNeighbors();

    if(getMineCount() == 0){
        revealNeighbors();
    }
    }
    
    }
}
}

//toggle on and off flagged via right click
void Tile::onClickRight() {
if(Toolbox::getInstance().gameState->getPlayStatus() == GameState::PLAYING){
    if(currentState == HIDDEN){
        setState(FLAGGED);
    }else if (currentState == FLAGGED){
        setState(HIDDEN);
    }
}
}


void Tile::draw() {
    // draw base, IE hidden or Revealed
    sf::Texture texture;
    
    std::string fileName;
    if(currentState == HIDDEN || currentState == FLAGGED){
        fileName = "./P4-data/images/tile_hidden.png";
    } else {
        fileName = "./P4-data/images/tile_revealed.png";
    }



    if (!texture.loadFromFile(fileName)) {
        std::cout << "Error loading tile image" << std::endl;
    }

    sf::Sprite sprite(texture);
    sprite.setPosition(position.x, position.y);

    Toolbox::getInstance().window.draw(sprite);

    //draw overlay, flagged, mine, or mine count
    
    if(currentState != HIDDEN){
        if(currentState == FLAGGED){
            fileName = "./P4-data/images/flag.png";
        } else if (currentState == EXPLODED){
            fileName = "./P4-data/images/mine.png";
        } else {
            switch(getMineCount()){
                case 0:
                    return;
                    break;
                case 1:
                   fileName = "./P4-data/images/number_1.png";
                   break;
                case 2:
                   fileName = "./P4-data/images/number_2.png";
                   break;
                case 3:
                   fileName = "./P4-data/images/number_3.png";
                   break;
                case 4:
                   fileName = "./P4-data/images/number_4.png";
                   break;
                case 5:
                   fileName = "./P4-data/images/number_5.png";
                   break;
                case 6:
                   fileName = "./P4-data/images/number_6.png";
                   break;
                case 7:
                   fileName = "./P4-data/images/number_7.png";
                   break;
                case 8:
                   fileName = "./P4-data/images/number_8.png";
                   break;

                default:
                   return;
                   break;
            }
        
        }

        


        if (!texture.loadFromFile(fileName)) {
            std::cout << "Error loading flag/mine overlay image" << std::endl;
        }

        sf::Sprite sprite(texture);
        sprite.setPosition(position.x, position.y);

        Toolbox::getInstance().window.draw(sprite);  
    }
}

void Tile::revealNeighbors() {
//do left lick on neighbors 
    for (Tile* neighbor : neighbors) {
        if (neighbor != nullptr && neighbor->getState() == HIDDEN) {
            neighbor->onClickLeft();
        }
    }
}

int Tile::getMineCount() {
//get number of mines round the tile
    int counter = 0;

    for (int i = 0; i < 8; i++) {

        if (neighbors[i] != nullptr && neighbors[i]->isMine) {
            counter++;
        }
    }

    return counter;
}

