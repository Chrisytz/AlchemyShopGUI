#include "Save.h"
#include <QtGui>
#include "Game.h"
#include "Label.h"
#include "splashScreen.h"
#include <QGuiApplication>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

extern Game *game;

//SaveButton::SaveButton() {
//    buttonSave = new QPushButton(tr(""));
//    buttonSave -> move(406, 456);
//    buttonSave->setStyleSheet("border-image:url(C:/Users/16136/CLionProjects/Alchemy-Shop-Testing/life.png);");
//    buttonSave -> setFixedSize(64,64);
//    connect(buttonSave, SIGNAL(clicked()), this, SLOT(onLeftButtonPressed()));
//    game -> scene -> addWidget(buttonSave);
//}
//
//void SaveButton::onLeftButtonPressed() {
//    qDebug() << "save button pressed";
//    //splashScreen();
//    game -> close();
//    game = new Game();
//    splashScreen *screen = new splashScreen();
//    Game::setPoints();
//    Label::setCount();
//}

Save::Save(int x, int y, QPixmap image) {
    x1 = x;
    y1 = y;
    image1 = image;

    setOffset(x1, y1);
    setPixmap(image1);
}

void Save::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event -> button() == Qt::LeftButton) {
        qDebug() << "save button pressed";
        //splashScreen();
        game->close();
        game = new Game();
        splashScreen *screen = new splashScreen();
        Game::setPoints();
        Label::setCount();
    }
}