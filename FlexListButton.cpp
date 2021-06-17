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
    buttonRestart = new QPushButton(tr(""));
    buttonRestart -> move(400, 20);
    buttonRestart->setStyleSheet("border-image:url(C:/Users/16136/CLionProjects/Alchemy-Shop-Testing/life.png);");
    buttonRestart -> setFixedSize(64,64);
    connect(buttonRestart, SIGNAL(clicked()), this, SLOT(onLeftButtonPressed()));
    game -> scene -> addWidget(buttonRestart);

}

void FlexListButton::onLeftButtonPressed() {
    qDebug() << "button pressed";
    //splashScreen();
    game -> close();
    qDebug() << "game closed";
    game = new Game();
    qDebug() << "new game created";
    game->delFlexList();
    game->delSaveGame();
    splashScreen *screen = new splashScreen();
    Game::setPoints();

    Label::setCount();
}