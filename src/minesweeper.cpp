#include "minesweeper.h"
#include "Toolbox.h"
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include <iostream>
#include <iomanip>

int main(){
	return launch();
}

int launch(){

//call rednering function
render();
    
    return 0;
}

//reset all
void restart() {
    if (Toolbox::getInstance().gameState != nullptr) {
        delete Toolbox::getInstance().gameState;
        Toolbox::getInstance().gameState = nullptr;
    }

    Toolbox::getInstance().gameState = new GameState(sf::Vector2i(25, 16), 50);

  sf::Texture* newGameTexture = new sf::Texture(); 
                sf::Sprite* newGameSprite = new sf::Sprite();  


                if (!newGameTexture->loadFromFile("./P4-data/images/face_happy.png")) {
                    std::cout << "Error loading new game image" << std::endl;
                } else {
                    newGameSprite->setTexture(*newGameTexture); 
                }

                Toolbox::getInstance().newGameButton->setSprite(newGameSprite);

    
}

//draw screen and board
void render(){
    Toolbox& toolBox = Toolbox::getInstance();

    toolBox.gameState = new GameState(sf::Vector2i(25, 16), 50);
    while (Toolbox::getInstance().window.isOpen()) {
        
        if (Toolbox::getInstance().gameState != nullptr) {
            sf::Event event;
            while (Toolbox::getInstance().window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    Toolbox::getInstance().window.close();
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(Toolbox::getInstance().window);
                    int x = mousePos.x / 32; // 32 is tile size
                    int y = mousePos.y / 32;
			//check if cliked on tile
                    if (x >= 0 && x < 25 && y >= 0 && y < 16) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            toolBox.gameState->getTile(x,y)->onClickLeft();
                        }
                        else if (event.mouseButton.button == sf::Mouse::Right) {
                            toolBox.gameState->getTile(x,y)->onClickRight();
                        }
                    } else {
                        // Check buttons
                        sf::FloatRect buttonBounds = toolBox.debugButton->getSprite()->getGlobalBounds();
                        if (buttonBounds.contains(static_cast<sf::Vector2f>(mousePos))) {
				toolBox.debugMode = !toolBox.debugMode;
				toggleDebugMode();
	
                            //toolBox.debugButton->onClick();
                        } else {
                            buttonBounds = toolBox.newGameButton->getSprite()->getGlobalBounds();
                            if (buttonBounds.contains(static_cast<sf::Vector2f>(mousePos))) {

                                toolBox.newGameButton->onClick();
                            } else {
                                buttonBounds = toolBox.testButton1->getSprite()->getGlobalBounds();
                                if (buttonBounds.contains(static_cast<sf::Vector2f>(mousePos))) {

                                    toolBox.testButton1->onClick();
                                } else {
                                    buttonBounds = toolBox.testButton2->getSprite()->getGlobalBounds();
                                    if (buttonBounds.contains(static_cast<sf::Vector2f>(mousePos))) {

                                        toolBox.testButton2->onClick();
                                    } else {

                                        buttonBounds = toolBox.testButton3->getSprite()->getGlobalBounds();

                                        if (buttonBounds.contains(static_cast<sf::Vector2f>(mousePos))) {

                                            toolBox.testButton3->onClick();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

        Toolbox::getInstance().window.clear(sf::Color::White);

        toggleDebugMode();

//draw tiles
if (toolBox.gameState != nullptr) {
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 25; x++) {
            toolBox.gameState->getTile(x,y)->draw();
        }
    }}
}

	//draw buttons
	toolBox.debugButton->getSprite();
toolBox.newGameButton->getSprite();
toolBox.testButton1->getSprite();
toolBox.testButton2->getSprite();
toolBox.testButton3->getSprite();

//logic for displaying flag counter
    sf::Texture digitsTexture;
    if (!digitsTexture.loadFromFile("./P4-data/images/digits.png"))
    {
        std::cerr << "Error loading digits image" << std::endl;
    }

//dice & dispaly digits
    int digitWidth = digitsTexture.getSize().x / 11;
    int digitHeight = digitsTexture.getSize().y;
 sf::Sprite digitSprites[11];

 for (int i = 0; i < 11; ++i)
    {

        digitSprites[i].setTexture(digitsTexture);
        digitSprites[i].setTextureRect(sf::IntRect(i * digitWidth, 0, digitWidth, digitHeight));
    }

        for (int i = 0; i < 11; ++i)
        {
            digitSprites[i].setPosition(i * (digitWidth + 10), 100); 
        }


	
	int flagCounter = 50 - toolBox.gameState->getFlagCount();

    std::stringstream ss;
    ss << std::setw(3) << std::setfill('0') << flagCounter; 
    std::string numStr = ss.str();

        int offsetX = 0; 
        for (char c : numStr)
        {
            int index;
            if (c == '-') {
                index = 10;
            } else {
                index = c - '0';
            }

            
            digitSprites[index].setPosition(offsetX, 512);
            Toolbox::getInstance().window.draw(digitSprites[index]);
            offsetX += digitWidth;
        }

//checking if game has been won
	bool isWin = true;


    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 25; x++) {
            if(!toolBox.gameState->getTile(x,y)->isMine && toolBox.gameState->getTile(x,y)->getState() != Tile::REVEALED){
isWin = false;		
}
        }
    }

	if(isWin){
        Toolbox::getInstance().gameState->setPlayStatus(GameState::WIN);
sf::Texture* newGameTexture = new sf::Texture(); 
                sf::Sprite* newGameSprite = new sf::Sprite();  


                if (!newGameTexture->loadFromFile("./P4-data/images/face_win.png")) {
                    std::cout << "Error loading new game image" << std::endl;
                } else {
                    newGameSprite->setTexture(*newGameTexture); 
                }

                Toolbox::getInstance().newGameButton->setSprite(newGameSprite);



	}



//display window
        Toolbox::getInstance().window.display();
    }

}

//dispaly debug menu
void toggleDebugMode() {
    


    Toolbox& toolBox = Toolbox::getInstance();
    if (toolBox.gameState != nullptr && Toolbox::getInstance().gameState->getPlayStatus() == GameState::PLAYING) {
        for (int y = 0; y < 16; y++) {
            for (int x = 0; x < 25; x++) {
                Tile& tile = *toolBox.gameState->getTile(x,y);
                if (toolBox.debugMode) {
                   	if (tile.isMine) {
                    tile.setState(Tile::EXPLODED);
}
                } else {
            
                    if (tile.isMine) {
			if(tile.getState() != Tile::FLAGGED){
                        tile.setState(Tile::HIDDEN); 
}
                    } 
                }
            }
        }
    }
}

//return debug mode
bool getDebugMode() {
Toolbox& toolBox = Toolbox::getInstance();
    return toolBox.debugMode; 
}


int gameLoop(){
	return 1;
}
