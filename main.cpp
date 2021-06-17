#include <iostream>
#include <QApplication>
#include "Label.h"
#include "Potion.h"
#include "Game.h"
#include "Customer.h"
#include "splashScreen.h"

using namespace std;

//initializing global object game
Game *game;

int main(int argc, char *argv[]) {
    //allows creation of application
    QApplication a(argc,argv);

    //creates a new game and shows it
    game = new Game();
    splashScreen *screen = new splashScreen();
    game->show();

    return a.exec();
}
