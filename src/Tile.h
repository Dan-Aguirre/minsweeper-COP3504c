#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <array>

class Tile {
public:
    enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED };

    bool isMine;

    Tile(sf::Vector2f position);

    sf::Vector2f getLocation();

    State getState();

    std::array<Tile*, 8>& getNeighbors();

    void setState(State _state);

    void setNeighbors(std::array<Tile*, 8> _neighbors);

    void onClickLeft();

    void onClickRight();

    void draw();

    



protected:
    void revealNeighbors();

private:
	int getMineCount();
    sf::Vector2f position;
    State currentState; 
    std::array<Tile*, 8> neighbors;
};

#endif