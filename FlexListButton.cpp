#include "FlexListButton.h"
#include <QtGui>
#include "Game.h"
#include "splashScreen.h"

extern Game *game;

//constructor
FlexListButton::FlexListButton() {
    //creates and formats restart button
    buttonRestart = new QPushButton(tr(""));
    buttonRestart -> move(470, 456);
    buttonRestart->setStyleSheet("border-image:url(C:/Users/16136/CLionProjects/AlchemyShopGUI/Restart.png);");
    buttonRestart -> setFixedSize(64,64);
    //connects signal to slot
    connect(buttonRestart, SIGNAL(clicked()), this, SLOT(onLeftButtonPressed()));
    //adds to scene
    game -> scene -> addWidget(buttonRestart);
}

//slot (executed when button is clicked to restart game and take to splashscreen)
void FlexListButton::onLeftButtonPressed() {
    //closes game and starts new one
    game -> close();
    game = new Game();
    //clears flex list and save game files
    game->delFlexList();
    game->delSaveGame();
    //creates splashscreen object (calls constructor which opens splashscreen)
    splashScreen *screen = new splashScreen();
    //resets points and potion count
    Game::setPoints();
    Label::setCount();
}