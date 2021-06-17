#include "FlexListTabs.h"
#include <QGuiApplication>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include "Game.h"
#include <QGraphicsRectItem>
#include "FlexListButton.h"

extern Game * game;

//constructor to make the invisible buttons (switch between tabs)
FlexListTabs::FlexListTabs(int x, int y) {
    setRect(x, y, 246, 26);
}

//functionality of switching tabs
void FlexListTabs::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    //getting mouse position
    int posx = event -> scenePos().x();
    int posy = event -> scenePos().y();
    //creating return button
    FlexListButton *returnButton = new FlexListButton();
    //when button is clicked
    if (event -> button() == Qt::LeftButton) {
        //creating background objects
        QGraphicsPixmapItem *backgroundChrono = new QGraphicsPixmapItem;
        backgroundChrono -> setPixmap(QPixmap("C:\\Users\\16136\\CLionProjects\\AlchemyShopGUI\\UI Flex List Tab 1.png"));
        QGraphicsPixmapItem *backgroundChronoBorder = new QGraphicsPixmapItem;
        backgroundChronoBorder -> setPixmap(QPixmap("C:\\Users\\16136\\CLionProjects\\AlchemyShopGUI\\UI Flex List Tab 1 Border.png"));
        QGraphicsPixmapItem *backgroundSorted = new QGraphicsPixmapItem;
        backgroundSorted -> setPixmap(QPixmap("C:\\Users\\16136\\CLionProjects\\AlchemyShopGUI\\UI Flex List Tab 2 (1).png"));
        QGraphicsPixmapItem *backgroundSortedBorder = new QGraphicsPixmapItem;
        backgroundSortedBorder -> setPixmap(QPixmap("C:\\Users\\16136\\CLionProjects\\AlchemyShopGUI\\UI Flex List Tab 2 Border.png"));
        game->scene->addItem(backgroundChrono);
        // if button clicked is the left tab
        if (posx > 31 && posx < 277 && posy > 27 && posy < 53) {
            //checks which tab is pressed (to be used in game)
            game->chronoPressed = true;
            game->scene->addItem(backgroundChrono);
            game->outputResults(game->scene, game->scrollValue);
            game->scene->addItem(backgroundChronoBorder);
            FlexListButton *returnButton = new FlexListButton();
        }
        //if button clicked is the right tab
        if (posx > 278 && posx < 524 && posy > 27 && posy <53) {
            //checks which tab is pressed (to be used in game)
            game->chronoPressed = false;
            game->scene->addItem(backgroundSorted);
            game->selectSort(game->getFlexList(),game->countLines() / 5, game->scene, game->scrollValue);
            game->scene->addItem(backgroundSortedBorder);
            FlexListButton *returnButton = new FlexListButton();
        }
    }
}