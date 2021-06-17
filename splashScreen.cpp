#include "splashScreen.h"
#include <QtGui>
#include "Game.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "Customer.h"
#include <fstream>
#include "Popup.h"

extern Game *game;

//constructor
splashScreen::splashScreen() {
    //clears scene and creates a new splashscreen on top of it
    game -> scene -> clear();
    QGraphicsRectItem *screen = new QGraphicsRectItem(0,0,554,540);
    screen -> setBrush(Qt::blue);
    game -> scene -> addItem(screen);

    //creates play game button
    play = new QPushButton(tr("&play game!"));
    play -> move(250, 260);
    //connects play game signal to slot
    connect(play, SIGNAL(clicked()), this, SLOT(onPlayPressed()));
    //adds to scene
    game -> scene -> addWidget(play);

    //creates an instructions button
    instructions = new QPushButton(tr("&instructions!"));
    instructions -> move(250, 380);
    //connects instructions button to slot
    connect(instructions, SIGNAL(clicked()), this, SLOT(onInstrPressed()));
    //adds to scene
    game -> scene -> addWidget(instructions);

    //checks if save game is empty to see whether to display load button (only if save game is not empty)
    ifstream read("saveGame.txt");
    if (read.peek() != ifstream::traits_type::eof()) {
        //creates and connects button, adds it to scene
        load = new QPushButton(tr("&load game"));
        load -> move(250, 350);
        connect(load, SIGNAL(clicked()), this, SLOT(onLoadPressed()));
        game -> scene -> addWidget(load);
    }
}

//starts game when button clicked
void splashScreen::onPlayPressed() {
    game -> close();
    Label::setCount();
    Potion::setCount();

    game = new Game();
    //generates initial customer ordering list
    game -> generateCustomerOrderingList(game->customerOrderingList, game->customerList, game->available, game->scene, game->customerTextList);
}

//instructions pop up displayed upon clicking the instructions button
void splashScreen::onInstrPressed() {
    //Popup object and instruction pop up method
    Popup info;
    info.popup_instr();
}

//fetches saved information and loads it into new game
void splashScreen::onLoadPressed() {
    game -> close();
    Label::setCount();
    Potion::setCount();
    game = new Game();
    game -> getInformation(game->customerOrderingList, game->available, game-> scene, game-> customerTextList);
}

