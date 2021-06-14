//
// Created by 16136 on 2021-06-14.
//
#include "splashScreen.h"
#include <QtGui>
#include "Game.h"
#include "Label.h"

extern Game *game;

splashScreen::splashScreen() {
    game -> scene -> clear();
    QGraphicsRectItem *screen = new QGraphicsRectItem(0,0,554,540);
    screen -> setBrush(Qt::blue);
    game -> scene -> addItem(screen);
    button = new QPushButton(tr("&play game!"));
    button -> move(250, 260);
    connect(button, SIGNAL(clicked()), this, SLOT(onLeftButtonPressed()));
    game -> scene -> addWidget(button);

}

void splashScreen::onLeftButtonPressed() {
    qDebug() << "button pressed";
    game -> close();
    Label::setCount();
    game = new Game();
}