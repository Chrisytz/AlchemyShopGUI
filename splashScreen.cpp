//
// Created by 16136 on 2021-06-14.
//
#include "splashScreen.h"
#include <QtGui>
#include "Game.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "Customer.h"


#include "Label.h"

extern Game *game;


splashScreen::splashScreen() {
    game -> scene -> clear();
    QGraphicsRectItem *screen = new QGraphicsRectItem(0,0,554,540);
    screen -> setBrush(Qt::blue);
    game -> scene -> addItem(screen);
    play = new QPushButton(tr("&play game!"));
    play -> move(250, 260);
    load = new QPushButton(tr("&load game"));
    load -> move(250, 350);
    connect(play, SIGNAL(clicked()), this, SLOT(onPlayPressed()));
    connect(load, SIGNAL(clicked()), this, SLOT(onLoadPressed()));
    game -> scene -> addWidget(play);
    game -> scene -> addWidget(load);

}

void splashScreen::onPlayPressed() {
    qDebug() << "button pressed";
    game -> close();
    Label::setCount();
    Potion::setCount();
    game = new Game();
    game -> generateCustomerOrderingList(game->customerOrderingList, game->customerList, game->available, game->scene, game->customerTextList);

}

void splashScreen::onLoadPressed() {
    qDebug() << "load button working ish";
    game -> close();
    Label::setCount();
    Potion::setCount();
    game = new Game();
    game -> getInformation(game->customerOrderingList, game->available, game-> scene, game-> customerTextList);

}

