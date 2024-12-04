#include "Toolbox.h"
#include "minesweeper.h"
#include "Button.h"
#include "iostream"
#include "GameState.h"



Toolbox* Toolbox::instance = nullptr;

Toolbox::Toolbox() {

debugMode = false;
//window frame
    window.create(sf::VideoMode(800, 600), "P4 – Minesweeper, Daniel Aguirre");


if (!debugTexture.loadFromFile("./P4-data/images/debug.png")) {
        std::cout << "Error loading debug image" << std::endl;
    }

//load buttons
if (!newGameTexture.loadFromFile("./P4-data/images/face_happy.png")) {
        std::cout << "Error loading new game image" << std::endl;
    }



    if (!testButton1Texture.loadFromFile("./P4-data/images/test_1.png")) {
        std::cout << "Error loading test button 1 image" << std::endl;
    }
    if (!testButton2Texture.loadFromFile("./P4-data/images/test_2.png")) {
        std::cout << "Error loading test button 2 image" << std::endl;
    }
    if (!testButton3Texture.loadFromFile("./P4-data/images/Test_3.png")) {
        std::cout << "Error loading test button 3 image" << std::endl;
    }


    debugSprite.setTexture(debugTexture);
    newGameSprite.setTexture(newGameTexture);
    testButton1Sprite.setTexture(testButton1Texture);
    testButton2Sprite.setTexture(testButton2Texture);
    testButton3Sprite.setTexture(testButton3Texture);  


    debugButton = new Button(sf::Vector2f(496, 512), []() {toggleDebugMode(); });
    debugButton->setSprite(&debugSprite);

    newGameButton = new Button(sf::Vector2f(368, 512), []() {restart(); });
    newGameButton->setSprite(&newGameSprite);


testButton1 = new Button(sf::Vector2f(560, 512), [this]() { 

    if (gameState) {
        delete gameState; 
    }
    gameState = new GameState("./P4-data/boards/testboard1.brd");
});
testButton1->setSprite(&testButton1Sprite);

testButton2 = new Button(sf::Vector2f(624, 512), [this]() { 

    if (gameState) { 
        delete gameState; 
    }
    gameState = new GameState("./P4-data/boards/testboard2.brd"); 
});
testButton2->setSprite(&testButton2Sprite);

testButton3 = new Button(sf::Vector2f(688, 512), [this]() { 

    if (gameState) {
        delete gameState;  
    }
    gameState = new GameState("./P4-data/boards/testboard3.brd"); 
});
testButton3->setSprite(&testButton3Sprite);


}
//return same instance
Toolbox& Toolbox::getInstance() {
    if (instance == nullptr) {
        instance = new Toolbox();
    }
    return *instance;
}

//destroyer
Toolbox::~Toolbox() {
    if (debugButton) {
        delete debugButton;
        debugButton = nullptr;
    }
    if (newGameButton) {
        delete newGameButton;
        newGameButton = nullptr;
    }
    if (testButton1) {
        delete testButton1;
        testButton1 = nullptr;
    }
    if (testButton2) {
        delete testButton2;
        testButton2 = nullptr;
    }
    if (testButton3) {
        delete testButton3;
        testButton3 = nullptr;
    }

    if (gameState) {
        delete gameState;
        gameState = nullptr;
    }
}
