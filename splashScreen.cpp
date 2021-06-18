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
    QGraphicsPixmapItem *screen = new QGraphicsPixmapItem;
    screen -> setPixmap(QPixmap("C:\\Users\\16136\\CLionProjects\\AlchemyShopGUI\\splashscreen.png"));
    game -> scene -> addItem(screen);

    //creates play game button
    play = new QPushButton();
    play -> move(29, 281);
    play->setStyleSheet("border-image:url(C:/Users/16136/CLionProjects/AlchemyShopGUI/playgame.png);");
    play -> setFixedSize(95,38);
    //connects play game signal to slot
    connect(play, SIGNAL(clicked()), this, SLOT(onPlayPressed()));
    //adds to scene
    game -> scene -> addWidget(play);

    //creates an instructions button
    instructions = new QPushButton(tr(""));
    instructions -> move(29, 410);
    instructions->setStyleSheet("border-image:url(C:/Users/16136/CLionProjects/AlchemyShopGUI/instructions.png);");
    instructions -> setFixedSize(95,38);
    //connects instructions button to slot
    connect(instructions, SIGNAL(clicked()), this, SLOT(onInstrPressed()));
    //adds to scene
    game -> scene -> addWidget(instructions);

    //checks if save game is empty to see whether to display load button (only if save game is not empty)
    ifstream read("saveGame.txt");
    if (read.peek() != ifstream::traits_type::eof()) {
        //creates and connects button, adds it to scene
        load = new QPushButton(tr(""));
        load -> move(29, 345);
        load->setStyleSheet("border-image:url(C:/Users/16136/CLionProjects/AlchemyShopGUI/loadgame.png);");
        load -> setFixedSize(95,38);
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

