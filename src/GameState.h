#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <string>
#include "Tile.h"

class GameState {
public:
    enum PlayStatus { WIN, LOSS, PLAYING };

    GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);

    GameState(const char* filepath);

    int getFlagCount();

    int getMineCount();

    Tile* getTile(int x, int y);

    PlayStatus getPlayStatus();

    void setPlayStatus(PlayStatus _status);

private:
    sf::Vector2i dimensions;
    int numberOfMines;
    std::vector<std::vector<Tile>> board;
    PlayStatus playStatus;
};

#endif
