//
// Created by 16136 on 2021-06-14.
//
#include "FlexListButton.h"
#include <QtGui>
#include "Game.h"
#include "Label.h"
#include "splashScreen.h"

extern Game *game;

FlexListButton::FlexListButton() {
    buttonRestart = new QPushButton(tr("&Return"));
    buttonRestart -> move(400, 20);
    connect(buttonRestart, SIGNAL(clicked()), this, SLOT(onLeftButtonPressed()));
    game -> scene -> addWidget(buttonRestart);

}

void FlexListButton::onLeftButtonPressed() {
    qDebug() << "button pressed";
    //splashScreen();
    game -> close();
    game = new Game();
    splashScreen *screen = new splashScreen();
    game->delFlexList();
    game->delSaveGame();
    Game::setPoints();

    Label::setCount();
}