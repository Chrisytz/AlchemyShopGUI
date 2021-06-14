#include <iostream>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include "Label.h"
#include "Potion.h"
#include "Game.h"
#include "Customer.h"

using namespace std;


Game *game;

int main(int argc, char *argv[]) {
    QApplication a(argc,argv);

    game = new Game();
    game->show();
//    do {
//        qDebug() << "hello UwU";
//        if (Game::play) {
//            game = new Game();
//            game->show();
//            qDebug() << Game::play;
//            continue;
//        }
//
//    } while (Game::points >= 0 && Game::points <= 10);

//    qDebug() << "loop exited";


    return a.exec();
}
