#include "GameState.h"
#include "Tile.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <random>


// Constructor for a random game state
GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines): dimensions(_dimensions), numberOfMines(_numberOfMines), playStatus(PLAYING) {


    board.resize(dimensions.y);

    for (int y = 0; y < dimensions.y; ++y) {
        for (int x = 0; x < dimensions.x; ++x) {
            sf::Vector2f position(x * 32.0f, y * 32.0f);
            board[y].emplace_back(position);
        }
    }

    // Random nums
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, dimensions.x - 1);
    std::uniform_int_distribution<> disY(0, dimensions.y - 1);

    int minesPlaced = 0;
    while (minesPlaced < numberOfMines) {
        int x = disX(gen);
        int y = disY(gen);
        Tile& tile = board[y][x];

        if (!tile.isMine) {
            tile.isMine = true;
            //tile.setState(Tile::EXPLODED);
            minesPlaced++;
        }
    }

}

GameState::GameState(const char* filepath) : playStatus(PLAYING) {


    // Open the file
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cout << "Could not open board" << std::endl;
        return; 
    }


    board.clear();

    std::string line;
    int y = 0;

    while (y < 16 && std::getline(file, line)) {

        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);


        if (line.empty()) {
            continue;
        }


        std::vector<Tile> row;
        for (int x = 0; x < line.size(); x++) {
            sf::Vector2f position(x * 32, y * 32);
            
            Tile tile(position);

            // Set the tile properties based on the character in the line
            if (line[x] == '0') {
                tile.isMine = false;
            } else {
                //tile.setState(Tile::EXPLODED); 
                tile.isMine = true;
            }

            row.push_back(tile); 
        }
        board.push_back(row); 
        y++;
    }


    file.close();


    numberOfMines = getMineCount();


}

//returns number of flags on board
int GameState::getFlagCount() {
    int count = 0;
    for (int y = 0; y < board.size(); ++y) {
        for (int x = 0; x < board[y].size(); ++x) {
            if (board[y][x].getState() == Tile::FLAGGED) {
                count++;
            }
        }
    }

    return count;
}

//returns number of mines on board
int GameState::getMineCount() {
    int count = 0;

    for (int y = 0; y < board.size(); ++y) {
        for (int x = 0; x < board[y].size(); ++x) {
            if (board[y][x].getState() == Tile::EXPLODED) {
                count++;
            }
        }
    }

    return count;
}

//returns tile at pos
Tile* GameState::getTile(int x, int y) {
    if (x < 0 || x >= board[y].size() || y < 0 || y >= board.size()) {
        return nullptr;
    }
    return &board[y][x];
}

GameState::PlayStatus GameState::getPlayStatus() {
    return playStatus;
}

void GameState::setPlayStatus(PlayStatus _status) {
    playStatus = _status;
}
