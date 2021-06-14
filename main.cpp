#include <iostream>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include "Label.h"
#include "Potion.h"
#include "Game.h"
#include "Customer.h"
#include "splashScreen.h"

using namespace std;


Game *game;

int main(int argc, char *argv[]) {
    QApplication a(argc,argv);

    game = new Game();
    splashScreen *screen = new splashScreen();
    game->show();

    return a.exec();
}
